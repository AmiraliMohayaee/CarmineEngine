#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "..\DevLibs\GLM\include\gtc\matrix_transform.hpp"
#include <vector>


class Cube
{
public:
	Cube();
	~Cube();
	void CreateBuffers();
	void Draw();
	void Update();


private:
	Buffer m_buffer;

	GLuint m_VAO;
	GLuint m_vertexVBO;
	GLuint m_colorsVBO;
	GLuint m_EBO;

	GLuint m_vertexAttributeID;
	GLuint m_colorAttributeID;

	glm::mat4 m_modelMatrix;

	GLuint m_modelUniformID;

	std::vector<GLfloat> m_vertexContainer;
	std::vector<GLfloat> m_colorContainer;
	std::vector<GLuint> m_indiciesContainer;
};