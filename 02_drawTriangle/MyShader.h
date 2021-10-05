#pragma once

#include "glad/glad.h"
#include <string>
#include <sstream>

class MyShader
{
public:
	// 构造器读取并构建着色器
	MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// 使用/激活程序
	void use();
	// uniform 工具函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	unsigned int ID;
};

