#pragma once

#include "Shader.h"
#include "Buffer.h"


class Grid
{
public:
	Grid();
	void SetupGridDimentions(int quadrants, int maxSize,
		float red, float green, float blue);

	void CreateBuffers();
	void DestroyBuffers();

	void Draw();
	void Update() {}
	

private:
	glm::vec3 m_color;

	Buffer m_buffer;

	glm::mat4 m_modelMatrix;

	GLuint m_modelUniformID;

	std::vector<GLfloat> m_vertexContainer;
	std::vector<GLfloat> m_colorContainer;
};