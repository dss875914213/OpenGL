#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>
#include "MyShader.h"

class MyOpenGL
{
public:
	MyOpenGL(int width, int height);
	~MyOpenGL();
	void SetViewPort();
	void SetVertexData();
	void SetIndexData();
	void BuildShaderProgram();
	void SetVertexAttribute();
	void SetVertexConfig();
	void SetTexture();
	void Render();
	static void ChangeAlpha(bool isUp);
	void Destroy();
private:
	int m_verticesSize;
	int m_indexSize;
	std::unique_ptr<float> m_vertices;
	std::unique_ptr<int> m_index;
	int m_width;
	int m_height;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_EBO;
	unsigned int m_vsShader;
	unsigned int m_fsShader;
	unsigned int m_shaderProgram;
	MyShader* m_shader;
	int m_imageWidth[2];
	int m_imageHeight[2];
	int m_imageChannels[2];
	unsigned char* m_imageData[2] = { NULL, NULL };
	unsigned int m_texture[2];
};

