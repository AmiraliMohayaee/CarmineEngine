#pragma once


#include "Shader.h"


class Buffer
{
public:
	Buffer();

	void GenerateBuffer(GLuint target, GLint size);
	void GenerateVertexArray(GLuint target, GLint size);

	void BindVertexArray(GLfloat* data, GLuint attributeData);
	void CloseVertexArray();

	void PopulateBuffer(GLfloat *data, GLuint attributeData);



private:



};