#include "ShaderProgram.hpp"

#include <iostream>

namespace PrismRender
{
	ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders)
	{
		programID = glCreateProgram();

		for (Shader shader : shaders)
		{
			glAttachShader(programID, shader.shaderID);
		}

		glLinkProgram(programID);

		int compiled = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, &compiled);
		if (!compiled)
		{
			int infoLogLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* infoLog = (char*)malloc(infoLogLength);
			glGetProgramInfoLog(programID, infoLogLength, &infoLogLength, infoLog);
			std::cerr << "[Error] Shader linking failed: " << infoLog << std::endl;
			free(infoLog);
		}

		for (Shader shader : shaders)
		{
			glDetachShader(programID, shader.shaderID);
			glDeleteShader(shader.shaderID);
		}
	}

	void ShaderProgram::bind() const
	{
		glUseProgram(programID);
	}

	void ShaderProgram::unbind() const
	{
		glUseProgram(0);
	}
}
