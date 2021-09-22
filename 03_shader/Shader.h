#pragma once
#include "GLEW/glew.h"

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();

public:
	GLuint Program;
};

