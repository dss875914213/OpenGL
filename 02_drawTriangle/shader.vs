#version 330 core

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec2 textureCoord;
out vec2 toFragmentTextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// gl_Position =projection* view* model * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
	gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
	toFragmentTextureCoord = textureCoord;
}

