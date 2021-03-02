#pragma once

#include "Buffer.h"
#include "Texture.h"
#include <gtc\matrix_transform.hpp>


class Cube
{
public:
	Cube();
	~Cube();
	void CreateBuffers();
	void DestroyBuffers();

	void Draw();
	void Update();


private:
	Buffer m_buffer;
	Texture m_texture;


	glm::vec3 m_position;
	glm::vec3 m_dimension;
	glm::mat4 m_modelMatrix;

	GLuint m_modelUniformID;
};