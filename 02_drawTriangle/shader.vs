#version 330 core

layout (location=0) in vec4 vertexPosition;

void main()
{
	gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
}

