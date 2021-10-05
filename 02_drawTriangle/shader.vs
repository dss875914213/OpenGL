#version 330 core

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexColor;
out vec3 toFragmentColor;

void main()
{
	gl_Position = vec4(vertexPosition.x, -vertexPosition.y, vertexPosition.z, 1.0f);
	toFragmentColor = vertexColor;
}

