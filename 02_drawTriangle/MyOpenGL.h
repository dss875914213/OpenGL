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
	void SetVertexData1();
	void SetVertexData2();
	void SetIndexData();
	void SetVertexShader();
	void SetFragmentShader1();
	void SetFragmentShader2();
	void BuildShaderProgram();
	void SetVertexAttribute();
	void SetVertexConfig();
	void Render();
	void Destroy();
private:
	int m_verticesSize;
	int m_indexSize;
	std::unique_ptr<float> m_vertices1;
	std::unique_ptr<float> m_vertices2;
	std::unique_ptr<int> m_index;
	int m_width;
	int m_height;
	unsigned int m_VBO[2];
	unsigned int m_VAO[2];
	unsigned int m_EBO;
	unsigned int m_vsShader;
	unsigned int m_fsShader[2];
	unsigned int m_shaderProgram[2];
	MyShader* m_shader;

};

