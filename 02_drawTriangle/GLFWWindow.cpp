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

	glfwSetKeyCallback(m_window, keyboardCallback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_window, mouseCallback);
	glfwSetScrollCallback(m_window, scrollCallback);
	m_openGL = new MyOpenGL(m_width, m_height);

	m_openGL->SetVertexConfig();
	m_openGL->BuildShaderProgram();
	m_openGL->SetViewPort();

	return true;
}

void GLFWWindow::Destroy()
{
	m_openGL->Destroy();
	glfwTerminate();
}

void GLFWWindow::Run()
{
	float lastTime, nowTime;
	nowTime = glfwGetTime();
	lastTime = nowTime;
	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_openGL->Render();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		nowTime = glfwGetTime();
		Camera::GetInstance()->setCameraSpeed(nowTime - lastTime);
		lastTime = nowTime;
	}
}

void GLFWWindow::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		MyOpenGL::ChangeAlpha(true);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		MyOpenGL::ChangeAlpha(false);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Camera::GetInstance()->changeCameraPos('w');
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Camera::GetInstance()->changeCameraPos('s');
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Camera::GetInstance()->changeCameraPos('a');
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Camera::GetInstance()->changeCameraPos('d');
	}
}

void GLFWWindow::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	static float lastXpos = xpos, lastYpos = ypos;
	float sensitivity = 0.05f;
	float xOffset, yOffset;
	xOffset = (xpos - lastXpos) * sensitivity;
	yOffset = (lastYpos - ypos) * sensitivity;
	lastXpos = xpos;
	lastYpos = ypos;

	Camera::GetInstance()->changeCameraFront(xOffset, yOffset);
}

void GLFWWindow::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::GetInstance()->SetFov(yoffset);
}
