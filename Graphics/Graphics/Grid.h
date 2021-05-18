#pragma once

#include "Shader.h"
#include "Buffer.h"


class Grid
{
public:

	Grid();
	void SetupGridDimentions(int quadrants, int maxSize,
		float red, float green, float blue, float alpha);

	void CreateBuffers();
	void DestroyBuffers();

	void Draw();
	void Update() {}
	

private:
	glm::vec4 m_color;

	Buffer m_buffer;

	glm::mat4 m_modelMatrix;

	GLuint m_modelUniformID;

};