#pragma once

#include <glm.hpp>
#include "glad.h"


class Material
{
public:
	Material();
	~Material();

	void SendToShader();


private:

	float m_shininess;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

