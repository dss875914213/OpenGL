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
	void changeValue();
	void changeValue(char order);

private:
	Camera();

private:
	static Camera* m_camera;
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	glm::mat4 m_view;
};

