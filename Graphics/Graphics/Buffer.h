#pragma once


#include "Shader.h"
#include <vector>


class Buffer
{
public:
	Buffer();

	// Generating VAOs and other buffers
	void GenerateVertexArray(GLsizei size, GLuint& target);
	void GenerateBuffer(GLsizei size, GLuint& target);
	
	// Binding buffers and VAOs
	void BindVertexArray(GLuint vertexArray);

	void BindVertices(GLuint& bufferObj, std::vector<GLfloat> data,
		GLuint attributeData);
	void BindColors(GLuint& bufferObj, std::vector<GLfloat> data,
		GLuint attributeData);

	void BindEBOArray(GLuint& bufferObj, std::vector<GLuint> data);
	void CloseVertexArray();


	void DisableVertexAttribute(GLuint attribute);
	void DeleteBuffer(GLuint buffer);
	void DeleteVertexArray(GLuint vertexArray);
};