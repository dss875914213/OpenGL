#pragma once
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Camera
{
public:
	static Camera* GetInstance();
	glm::mat4 calculate1();
	glm::mat4 calculate2();
	void changeCameraPos();
	void changeCameraPos(char order);
	void changeCameraFront(float xoffset, float yoffset);
	void setCameraSpeed(float deltaTime);
	void SetFov(double offset);
	float GetFov();
	static glm::mat4 myLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up);

private:
	Camera();

private:
	static Camera* m_camera;
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	glm::mat4 m_view;
	float m_cameraSpeed;
	float m_pitch = 0.0f;
	float m_yam = -90.0f;
	float m_fov = 45;
};

