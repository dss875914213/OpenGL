#include "Camera.h"

Camera* Camera::m_camera = NULL;

Camera::Camera() :
	m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
	m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_view (glm::mat4(1.0f))
{

}

void Camera::changeValue()
{
	float radius = 5.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	m_cameraPos = glm::vec3(camX, 0.0f, camZ);
}

void Camera::changeValue(char order)
{
	float cameraSpeed = 0.05f;
	switch (order)
	{
	case 'w':
		m_cameraPos += cameraSpeed * m_cameraFront;
		break;
	case 's':
		m_cameraPos -= cameraSpeed * m_cameraFront;
		break;
	case 'a':
		m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		break;
	case 'd':
		m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
		break;
	}
}

Camera* Camera::GetInstance()
{
	if (Camera::m_camera == NULL)
		Camera::m_camera = new Camera();
	return Camera::m_camera;
}

glm::mat4 Camera::calculate1()
{
	m_view = glm::lookAt(m_cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), m_cameraUp);
	return m_view;
}

glm::mat4 Camera::calculate2()
{
	m_view = glm::lookAt(m_cameraPos, m_cameraPos+m_cameraFront, m_cameraUp);
	return m_view;
}
