#version 460 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 textureCoords;

out vec2 textureCoordinates;

void main()
{
	gl_Position = vec4(vertexPos, 1.0f);
	textureCoordinates = textureCoords;
}