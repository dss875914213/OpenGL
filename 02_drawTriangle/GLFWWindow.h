#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "MyOpenGL.h"

class GLFWWindow
{
public:
	GLFWWindow(int width, int height);
	~GLFWWindow();
	void Initialize();
	bool CreateWindow();
	void Destroy();
	void Run();
private:
	static void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	int m_width;
	int m_height;
	GLFWwindow* m_window;
	MyOpenGL* m_openGL;
};

