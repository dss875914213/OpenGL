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
	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
private:
	int m_width;
	int m_height;
	GLFWwindow* m_window;
	MyOpenGL* m_openGL;
};

