#include "Buffer.h"

Buffer::Buffer()
{

}

void Buffer::GenerateBuffer(GLuint target, GLint size)
{
	glGenBuffers(size, &target);
	glBindBuffer(GL_ARRAY_BUFFER, target);
}

void Buffer::GenerateVertexArray(GLuint target, GLint size)
{
	glGenVertexArrays(size, &target);
}

void Buffer::BindVertexArray(GLfloat *data, GLuint attributeData)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeData, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attributeData);
}

// To close the Vertex array contents when done with populating it
void Buffer::CloseVertexArray()
{
	glBindVertexArray(0);
}

void Buffer::PopulateBuffer(GLfloat *data, GLuint attributeData)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeData, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attributeData);
}

