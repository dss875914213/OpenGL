#version 330 core

layout (location=0) in vec4 vertexPosition;
out vec4 vertexColor;

void main()
{
	gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
	vertexColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

