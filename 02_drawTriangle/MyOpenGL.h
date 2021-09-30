#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class MyOpenGL
{
public:
	MyOpenGL(int width, int height);
	~MyOpenGL();
	void SetViewPort();
	void SetVertexData();
	void SetVertexShader();
	void SetFragmentShader();
	void BuildShaderProgram();
	void SetVertexAttribute();
	void SetVAO();
	void Render();
private:
	float *m_vertices;
	int m_verticesSize;
	int m_width;
	int m_height;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_vsShader;
	unsigned int m_fsShader;
	unsigned int m_shaderProgram;
};

