#pragma once

#include <glm.hpp>
#include "glad.h"
#include "Buffer.h"
#include "Object.h"

class Light : public Object
{

public:

	Light(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);
	virtual ~Light() {}

	virtual void Create();
	virtual void Destroy();
	virtual void Update() {}
	virtual void Draw();                 //for debug only!

	void SendToShader();

	void LightMovementControl(float cameraMoveSpeed);

private:

	Buffer m_buffer;

	glm::vec3 m_forward;
	glm::vec3 m_up;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};