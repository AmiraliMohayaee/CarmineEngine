#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"
#include <gtc\matrix_transform.hpp>
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
	Texture m_texture;

	//GLuint m_vertexAttributeID;
	//GLuint m_colorAttributeID;
	//GLuint m_textureAttributeID;

	glm::vec3 m_dimention;
	glm::mat4 m_modelMatrix;

	GLuint m_modelUniformID;

	//std::vector<GLfloat> m_vertexContainer;
	//std::vector<GLfloat> m_colorContainer;
	//std::vector<GLfloat> m_uvContainer;
	//std::vector<GLuint> m_indiciesContainer;
};