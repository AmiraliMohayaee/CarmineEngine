#pragma once

#include "Buffer.h"
#include "Texture.h"
#include "Model.h"
#include "Material.h"
#include <gtc\matrix_transform.hpp>


class Cube
{

public:
	Cube();
	~Cube();
	void CreateBuffers();
	void DestroyBuffers();

	void IsTextured(bool flag);
	void IsLit(bool flag);

	void Draw();
	void Update();


private:

	bool m_isTextured = false;
	bool m_isLit = false;

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;

	glm::vec3 m_position;
	glm::vec3 m_dimension;
	glm::mat4 m_modelMatrix;

};