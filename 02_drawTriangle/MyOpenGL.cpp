#include "MyOpenGL.h"
#include <iostream>
#include <string>

MyOpenGL::MyOpenGL(int width, int height)
	:m_verticesSize(18), m_indexSize(6),
	m_vertices(new float[m_verticesSize]),
	m_index(new int[m_indexSize]),
	m_width(width), m_height(height)
{

	float vertices1[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

	memcpy(m_vertices.get(), vertices1, m_verticesSize * sizeof(float));

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

MyOpenGL::~MyOpenGL()
{

}

void MyOpenGL::SetViewPort()
{
	glViewport(0, 0, m_width, m_height);
}

void MyOpenGL::SetVertexData()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_verticesSize, m_vertices.get(), GL_STATIC_DRAW);
}

void MyOpenGL::SetIndexData()
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indexSize, m_index.get(), GL_STATIC_DRAW);
}

void MyOpenGL::BuildShaderProgram()
{
	m_shader = new MyShader("D:\\1_WorkSpace\\1_Coding\\OpenGL\\02_drawTriangle\\shader.vs", 
		"D:\\1_WorkSpace\\1_Coding\\OpenGL\\02_drawTriangle\\shader.fs");
}

void MyOpenGL::SetVertexAttribute()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
}

void MyOpenGL::SetVertexConfig()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	SetVertexData();
	SetVertexAttribute();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MyOpenGL::Render()
{
	m_shader->use();
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MyOpenGL::Destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shaderProgram);
}
