#include "MyOpenGL.h"
#include <iostream>
#include <string>

MyOpenGL::MyOpenGL(int width, int height)
	:m_vertices(nullptr), m_width(width), m_height(height)
{
	m_verticesSize = 9;
	m_vertices = new float[m_verticesSize];

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};
	memcpy(m_vertices, vertices, m_verticesSize * sizeof(float));

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

MyOpenGL::~MyOpenGL()
{
	delete[] m_vertices;
}

void MyOpenGL::SetViewPort()
{
	glViewport(0, 0, m_width, m_height);
}

void MyOpenGL::SetVertexData()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_verticesSize, m_vertices, GL_STATIC_DRAW);
}

void MyOpenGL::SetVertexShader()
{
	const char* vertexShaderSources =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

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
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";;
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
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vsShader);
	glAttachShader(m_shaderProgram, m_fsShader);
	glLinkProgram(m_shaderProgram);
	int success;
	char log[512];
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
	}
	glDeleteShader(m_vsShader);
	glDeleteShader(m_fsShader);
}

void MyOpenGL::SetVertexAttribute()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MyOpenGL::SetVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
}

void MyOpenGL::Render()
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
