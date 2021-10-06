#include "MyOpenGL.h"
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float g_alpha = 0.5 ;

MyOpenGL::MyOpenGL(int width, int height)
	:m_verticesSize(32), m_indexSize(6),
	m_vertices(new float[m_verticesSize]),
	m_index(new int[m_indexSize]),
	m_width(width), m_height(height)
{

	float vertices[] = {
		// 位置              颜色            纹理坐标
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f};

	int index[] = {
		0, 1, 2,
		0, 2, 3 };

	memcpy(m_vertices.get(), vertices, m_verticesSize * sizeof(float));
	memcpy(m_index.get(), index, m_indexSize * sizeof(float));

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void MyOpenGL::SetVertexConfig()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	SetVertexData();
	SetIndexData();
	SetVertexAttribute();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	SetTexture();
}

void MyOpenGL::SetTexture()
{
	stbi_set_flip_vertically_on_load(true);

	m_imageData[0] = stbi_load("D:\\1_WorkSpace\\1_Coding\\OpenGL\\Dependencies\\resource\\container.jpg", &m_imageWidth[0], &m_imageHeight[0], &m_imageChannels[0], 0);
	m_imageData[1] = stbi_load("D:\\1_WorkSpace\\1_Coding\\OpenGL\\Dependencies\\resource\\awesomeface.png", &m_imageWidth[1], &m_imageHeight[1], &m_imageChannels[1], 0);
	glGenTextures(1, &m_texture[0]);
	glGenTextures(1, &m_texture[1]);
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_imageWidth[0], m_imageHeight[0], 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, m_texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_imageWidth[1], m_imageHeight[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData[1]);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(m_imageData[0]);
	stbi_image_free(m_imageData[1]);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void MyOpenGL::SetTransform()
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	unsigned int transformLoc = glGetUniformLocation(m_shader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void MyOpenGL::Render()
{
	m_shader->use();
	m_shader->setInt("myTexure1", 0);
	m_shader->setInt("myTexure2", 1);
	m_shader->setFloat("alpha", g_alpha);
	SetTransform();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture[1]);
	glBindVertexArray(m_VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MyOpenGL::ChangeAlpha(bool isUp)
{
	if (isUp)
	{
		g_alpha += 0.1;
	}
	else
	{
		g_alpha -= 0.1;
	}
	g_alpha = g_alpha >= 1.0 ? 1.0 : g_alpha;
	g_alpha = g_alpha <= 0.0 ? 0.0 : g_alpha;
}

void MyOpenGL::Destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shaderProgram);
}
