#pragma once

#include "Shader.h"
#include "..\DevLibs\GLM\include\gtc\matrix_transform.hpp"


class Camera
{
public:
	Camera();
	~Camera();
	bool InitCamera(float x, float y, float z, float fov, 
		float close, float far);

	void SetViewAndProJ();

	void UpdateCamera();


private:
	GLuint m_viewUniformID;
	GLuint m_projUniformID;

	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraForward;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

};