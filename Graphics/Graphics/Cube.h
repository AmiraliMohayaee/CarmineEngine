#pragma once

//#include "..\DevLibs\GLM\include\gtc\matrix_transform.hpp"
#include "Shader.h"


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
	GLuint m_modelUniformID;
	GLuint m_viewUniformID;

	//glm::vec3 m_cameraPos;
	//glm::vec3 m_cameraUp;
	//glm::vec3 m_cameraForward;

	//glm::mat4 m_modelMatrix;
	//glm::mat4 m_viewMatrix;

};