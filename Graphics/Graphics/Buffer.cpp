#include "Buffer.h"


Buffer::Buffer()
{

}

//==========================================================================
//	Functions creating VAOs, VBOs and EBOs
//==========================================================================
void Buffer::GenerateBuffer(GLsizei size, GLuint& target)
{
	glGenBuffers(size, &target);
}

void Buffer::GenerateVertexArray(GLsizei size, GLuint& target)
{
	glGenVertexArrays(size, &target);
}

void Buffer::BindVertexArray(GLuint vertexArray)
{
	glBindVertexArray(vertexArray);
}

void Buffer::BindVertices(GLuint& bufferObj, std::vector<GLfloat> data,
	GLuint attributeData)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attributeData, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attributeData);
}

void Buffer::BindColors(GLuint& bufferObj, std::vector<float> data, 
	GLuint attributeData)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attributeData, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attributeData);
}

void Buffer::BindEBOArray(GLuint& bufferObj, std::vector<GLuint> data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * data.size(), &data[0], GL_STATIC_DRAW);
}

//==========================================================================
// To close the Vertex array contents when done with populating it
//==========================================================================
void Buffer::CloseVertexArray()
{
	glBindVertexArray(0);
}


//==========================================================================
//	Functions for deleting buffer and vertex attribute elements
//==========================================================================
void Buffer::DisableVertexAttribute(GLuint attribute)
{
	glDisableVertexAttribArray(attribute);
}

void Buffer::DeleteBuffer(GLuint buffer)
{
	glDeleteBuffers(1, &buffer);
}

void Buffer::DeleteVertexArray(GLuint vertexArray)
{
	glDeleteVertexArrays(1, &vertexArray);
}
