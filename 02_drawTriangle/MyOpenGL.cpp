#include "MyOpenGL.h"
#include <iostream>
#include <string>

MyOpenGL::MyOpenGL(int width, int height)
	:m_verticesSize(9), m_indexSize(6),
	m_vertices1(new float[m_verticesSize]),
	m_vertices2(new float[m_verticesSize]),
	m_index(new int[m_indexSize]),
	m_width(width), m_height(height)
{

	float vertices1[] = {
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f};
	
	float vertices2[] = {
		 0.0f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f};

	int index[] = {
		0,1,2,
		0,2,3
	};
	memcpy(m_vertices1.get(), vertices1, m_verticesSize * sizeof(float));
	memcpy(m_vertices2.get(), vertices2, m_verticesSize * sizeof(float));
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

void MyOpenGL::SetVertexData1()
{
	glGenBuffers(1, &m_VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_verticesSize, m_vertices1.get(), GL_STATIC_DRAW);
}

void MyOpenGL::SetVertexData2()
{
	glGenBuffers(1, &m_VBO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_verticesSize, m_vertices2.get(), GL_STATIC_DRAW);
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

void MyOpenGL::SetFragmentShader1()
{
	const char* fragShaderSources =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n";
	m_fsShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fsShader[0], 1, &fragShaderSources, NULL);
	glCompileShader(m_fsShader[0]);
	int success;
	char log[512];
	glGetShaderiv(m_fsShader[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fsShader[0], 512, NULL, log);
		std::cout << "Failed to Compile fragment shader " << log << std::endl;
	}
}

void MyOpenGL::SetFragmentShader2()
{
	const char* fragShaderSources =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";
	m_fsShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fsShader[1], 1, &fragShaderSources, NULL);
	glCompileShader(m_fsShader[1]);
	int success;
	char log[512];
	glGetShaderiv(m_fsShader[1], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fsShader[1], 512, NULL, log);
		std::cout << "Failed to Compile fragment shader " << log << std::endl;
	}
}

void MyOpenGL::BuildShaderProgram()
{
	m_shader = new MyShader("D:\\1_WorkSpace\\1_Coding\\OpenGL\\02_drawTriangle\\shader.vs", 
		"D:\\1_WorkSpace\\1_Coding\\OpenGL\\02_drawTriangle\\shader.fs");

	//SetVertexShader();
	//SetFragmentShader1();
	//SetFragmentShader2();
	//m_shaderProgram[0] = glCreateProgram();
	//m_shaderProgram[1] = glCreateProgram();
	//glAttachShader(m_shaderProgram[0], m_vsShader);
	//glAttachShader(m_shaderProgram[0], m_fsShader[0]);
	//glLinkProgram(m_shaderProgram[0]);

	//glAttachShader(m_shaderProgram[1], m_vsShader);
	//glAttachShader(m_shaderProgram[1], m_fsShader[1]);
	//glLinkProgram(m_shaderProgram[1]);
	//int success;
	//char log[512];
	//glGetShaderiv(m_shaderProgram[0], GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(m_shaderProgram[0], 512, NULL, log);
	//	std::cout << "Failed to link shader " << log << std::endl;
	//}
	//glDeleteShader(m_vsShader);
	//glDeleteShader(m_fsShader[0]);
	//glDeleteShader(m_fsShader[1]);
}

void MyOpenGL::SetVertexAttribute()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void MyOpenGL::SetVertexConfig()
{
	glGenVertexArrays(1, &m_VAO[0]);
	glBindVertexArray(m_VAO[0]);
	SetVertexData1();
	SetVertexAttribute();
	//SetIndexData();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &m_VAO[1]);
	glBindVertexArray(m_VAO[1]);
	SetVertexData2();
	SetVertexAttribute();
	//SetIndexData();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MyOpenGL::Render()
{
	m_shader->use();
	//glUseProgram(m_shaderProgram[0]);
	glBindVertexArray(m_VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glUseProgram(m_shaderProgram[1]);
	glBindVertexArray(m_VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MyOpenGL::Destroy()
{
	glDeleteVertexArrays(1, &m_VAO[0]);
	glDeleteBuffers(1, &m_VBO[0]);
	glDeleteVertexArrays(1, &m_VAO[1]);
	glDeleteBuffers(1, &m_VBO[1]);
	glDeleteProgram(m_shaderProgram[0]);
	glDeleteProgram(m_shaderProgram[1]);
}
