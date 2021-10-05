#pragma once

#include "glad/glad.h"
#include <string>
#include <sstream>

class MyShader
{
public:
	// ��������ȡ��������ɫ��
	MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// ʹ��/�������
	void use();
	// uniform ���ߺ���
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	unsigned int ID;
};

