#pragma once

#include "Buffer.h"
#include "Texture.h"
#include "Material.h"
#include "Object.h"


class Cube : public Object
{

public:

	Cube(GLfloat width = 1.0f, GLfloat height = 1.0f, GLfloat depth = 1.0f,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat alpha = 1.0f);
	~Cube();

	void SetDimension(const glm::vec3& dimensions);
	void SetDimension(GLfloat width, GLfloat height, GLfloat depth);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha = 1.0f);

	virtual void Create();
	virtual void Update() {}
	virtual void Draw(const Shader& shader);
	virtual void Destroy();


private:

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;

	glm::vec3 m_dimension;
	glm::vec4 m_color;

};