#pragma once

#include "Shader.h"
#include <gtc\matrix_transform.hpp>


class Camera
{
public:
	Camera();
	~Camera();
	bool InitCamera(float x, float y, float z, float fov, 
		float close, float far);

	void CameraMouseMovement(float mouseSensitivity);
	void CameraKeyboardMovement(float camMoveSpeed);

	void SetViewAndProJ();
	void UpdateCamera();


private:
	GLuint m_viewUniformID;
	GLuint m_projUniformID;

	// Angles for pitch and yaw on camera
	// rotation
	float m_pitch;
	float m_yaw;

	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraForward;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

};