#include "MyOpenGL.h"
#include <iostream>
#include <string>

MyOpenGL::MyOpenGL(int width, int height)
	:m_verticesSize(18), m_indexSize(6),
	m_vertices(new float[m_verticesSize]),
	m_index(new int[m_indexSize]),
	m_width(width), m_height(height)
{

	float vertices[] = {
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f};

	int index[] = {
		0,1,2,
		0,2,3
	};
	memcpy(m_vertices.get(), vertices, m_verticesSize * sizeof(float));
	memcpy(m_index.get(), index, m_indexSize * sizeof(int));

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

void MyOpenGL::SetVertexShader()
{
	const char* vertexShaderSources =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\n";

	m_vsShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vsShader, 1, &vertexShaderSources, NULL);
	glCompileShader(m_vsShader);
	int success;
	char log[512];
	glGetShaderiv(m_vsShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_vsShader, 512, NULL, log);
		std::cout << "Failed to Compile vertex shader " << log << std::endl;
	}
}

void MyOpenGL::SetFragmentShader()
{
	const char* fragShaderSources =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";
	m_fsShader =glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fsShader, 1, &fragShaderSources, NULL);
	glCompileShader(m_fsShader);
	int success;
	char log[512];
	glGetShaderiv(m_fsShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fsShader, 512, NULL, log);
		std::cout << "Failed to Compile fragment shader " << log << std::endl;
	}
}

void MyOpenGL::BuildShaderProgram()
{
	SetVertexShader();
	SetFragmentShader();
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vsShader);
	glAttachShader(m_shaderProgram, m_fsShader);
	glLinkProgram(m_shaderProgram);
	int success;
	char log[512];
	glGetShaderiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_shaderProgram, 512, NULL, log);
		std::cout << "Failed to link shader " << log << std::endl;
	}
	glDeleteShader(m_vsShader);
	glDeleteShader(m_fsShader);
}

void MyOpenGL::SetVertexAttribute()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void MyOpenGL::SetVertexConfig()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	SetVertexData();
	SetVertexAttribute();
	SetIndexData();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MyOpenGL::Render()
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MyOpenGL::Destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shaderProgram);
}
