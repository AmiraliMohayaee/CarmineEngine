#pragma once

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"

class Light : public Object
{

public:

	Light(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);
	virtual ~Light() {};

	virtual void Create();
	virtual void Draw(const Shader& shader);                 //for debug only!
	virtual void Update() {}
	virtual void Destroy();

	void SendToShader(const Shader& shader);

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