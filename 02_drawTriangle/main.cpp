#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <thread>
#include "GLFWWindow.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	GLFWWindow* glfwWindow = new GLFWWindow(WIDTH, HEIGHT);
	glfwWindow->Initialize();
	glfwWindow->CreateWindow();
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwWindow->Run();
	//std::thread t = std::thread(&GLFWWindow::Run, glfwWindow);
	//t.join();
	glfwWindow->Destroy();
}

