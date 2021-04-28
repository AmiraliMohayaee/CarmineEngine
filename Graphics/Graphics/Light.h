#pragma once

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"

class Light
{

public:

	Light(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);

	void CreateBuffers();
	void Render();                 //for debug only!
	void SendToShader();
	void DestroyBuffers();

	void LightMovementControl(float cameraMoveSpeed);

private:

	Buffer m_buffer;

	glm::vec3 m_position;
	glm::mat4 m_modelMatrix;

	glm::vec3 m_forward;
	glm::vec3 m_up;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};