#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"
#include "..\DevLibs\GLM\include\gtc\matrix_transform.hpp"
#include <vector>



class Quad
{
public:
	Quad();
	~Quad() {}
	void CreateBuffers();
	void DestroyBuffer();

	void Draw();
	void Update();


private:
	Buffer m_buffer;
	Texture m_texture;

	glm::mat4 m_modelMatrix;
	glm::vec3 m_dimension;
};