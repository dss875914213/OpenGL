#include "Camera.h"

Camera::Camera() :
	m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
	m_cameraFront(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_view (glm::mat4(1.0f))
{

}

void Camera::changeValue()
{
	float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	m_cameraPos = glm::vec3(camX, 0.0f, camZ);
}

glm::mat4 Camera::calculate()
{
	m_view = glm::lookAt(m_cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), m_cameraUp);
	return m_view;
}
