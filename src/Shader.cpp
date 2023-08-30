#include "Shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace PrismRender
{
	Shader::Shader(const char* shaderFilePath, int shaderType)
	{
		std::string shaderSource;
		std::ifstream shaderFile;

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			std::stringstream shaderStream;
			shaderFile.open(shaderFilePath);
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			shaderSource = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cerr << "[Error] Failed to read shader source file" << std::endl;
			return;
		}
		const char* shaderCode = shaderSource.c_str();

		shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shaderCode, NULL);
		glCompileShader(shaderID);

		int compiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			int infoLogLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* infoLog = (char*)malloc(infoLogLength);
			glGetShaderInfoLog(shaderID, infoLogLength, &infoLogLength, infoLog);
			std::cerr << "[Error] Shader compilation failed: " << infoLog << std::endl;
			free(infoLog);
			glDeleteShader(shaderID);
		}
	}
}