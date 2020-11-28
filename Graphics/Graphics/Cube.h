#pragma once

#include "Shader.h"
#include "..\DevLibs\GLM\include\gtc\matrix_transform.hpp"


class Cube
{
public:
	Cube();
	~Cube();
	void CreateBuffers();
	void Draw();
	void Update();


private:
	GLuint m_VAO;
	GLuint m_vertexVBO;
	GLuint m_colorsVBO;
	GLuint m_EBO;

	GLuint m_vertexAttributeID;
	GLuint m_colorAttributeID;

	glm::mat4 m_modelMatrix;

	GLuint m_modelUniformID;
};