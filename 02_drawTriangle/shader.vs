#version 330 core

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexColor;
out vec3 toFragmentColor;
uniform float offSet;

void main()
{
	gl_Position = vec4(vertexPosition.x+offSet, vertexPosition.y, vertexPosition.z, 1.0f);
	toFragmentColor = vertexColor;
}

