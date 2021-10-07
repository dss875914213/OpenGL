#include "Camera.h"

Camera* Camera::m_camera = NULL;

Camera::Camera() :
	m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
	m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_view (glm::mat4(1.0f)),
	m_cameraSpeed(0.05f)
{

}

void Camera::changeCameraPos()
{
	float radius = 5.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	m_cameraPos = glm::vec3(camX, 0.0f, camZ);
}

void Camera::changeCameraPos(char order)
{
	switch (order)
	{
	case 'w':
		m_cameraPos += m_cameraSpeed * m_cameraFront;
		break;
	case 's':
		m_cameraPos -= m_cameraSpeed * m_cameraFront;
		break;
	case 'a':
		m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed;
		break;
	case 'd':
		m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed;
		break;
	}
}

void Camera::changeCameraFront(float xoffset, float yoffset)
{
	m_pitch += yoffset;
	m_yam += xoffset;
	m_pitch = m_pitch > 89 ? 89 : m_pitch;
	m_pitch = m_pitch < -89 ? -89 : m_pitch;
	m_cameraFront.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yam));
	m_cameraFront.y = sin(glm::radians(m_pitch));
	m_cameraFront.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yam));
	m_cameraFront = glm::normalize(m_cameraFront);
}

void Camera::setCameraSpeed(float deltaTime)
{
	m_cameraSpeed = 2.5f * deltaTime;
}

void Camera::SetFov(double offset)
{
	m_fov -= offset;
	m_fov = m_fov <= 1.0f ? 1.0f : m_fov;
	m_fov = m_fov >= 45.0f ? 45.0f : m_fov;
}

float Camera::GetFov()
{
	return m_fov;
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
