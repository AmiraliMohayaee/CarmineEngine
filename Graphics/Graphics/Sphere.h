#pragma once

#include "Object.h"


class Sphere :	public Object
{
public:

	Sphere(GLfloat radius = 1.0f, GLuint sectors = 36, GLuint stacks = 18, GLfloat r = 1.0f,
		GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat alpha = 1.0f);
	~Sphere();

	void SetRadius(GLfloat radius);
	void SetStackCount(GLint stacks);
	void SetSectorCount(GLint sectors);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha = 1.0f);

	GLfloat GetRadius() const;
	GLuint GetStackCount() const;
	GLuint GetSectorCount() const;

	virtual void Create();
	virtual void Destroy();
	virtual void Draw();
	virtual void Update();


private:

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;

	GLuint m_stacks;
	GLuint m_sectors;
	GLfloat m_radius;

	glm::vec4 m_color;
	glm::vec3 m_dimension;

};

