#include "GLFWWindow.h"
#include <iostream>

GLFWWindow::GLFWWindow(int width, int height)
	:m_width(width), m_height(height), m_window(NULL)
{

}

void GLFWWindow::Initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool GLFWWindow::CreateWindow()
{
	m_window = glfwCreateWindow(m_width, m_height, "dssOpenGL", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to glfwCreateWindow" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, processInput);
	return true;
}

void GLFWWindow::Destroy()
{
	glfwTerminate();
}

void GLFWWindow::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void GLFWWindow::processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
