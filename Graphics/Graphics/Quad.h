#pragma once

#include "Object.h"
#include "glad.h"
#include "Buffer.h"
#include "Texture.h"
#include "Material.h"

class Quad : public Object
{
public:

	Quad(GLfloat width = 1.0f, GLfloat height = 1.0f,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat alpha = 1.0f);
	virtual ~Quad() {}

	virtual void Create();
	virtual void Destroy();
	virtual void Draw();
	virtual void Update() {}

	void SetDimension(GLfloat width, GLfloat height);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha = 1.0f);

private:

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;

	glm::vec4 m_color;
	glm::vec3 m_dimension;

};