#include "Buffer.h"


Buffer::Buffer()
{
	m_VAO = 0;
	m_EBO = 0;
	m_hasEBO = false;
	m_totalVertices = 0;

	//for (int i = 0; i < TOTAL_BUFFERS; i++)
	//{
	//	m_VBOs[i] = 0;
	//}

	for (auto& i : m_VBOs)
	{
		i = 0;
	}
}

void Buffer::Create(GLuint totalVertices, bool hasEBO)
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(TOTAL_BUFFERS, m_VBOs);

	if (hasEBO)
	{
		glGenBuffers(1, &m_EBO);
	}

	m_hasEBO = hasEBO;
	m_totalVertices = totalVertices;
}

void Buffer::FillVBO(VBOType bufferType, GLfloat* data, GLsizeiptr bufferSize, FillType fillType)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[bufferType]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, fillType);
}

void Buffer::FillEBO(GLuint* data, GLsizeiptr bufferSize, FillType fillType)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, data, fillType);
}

void Buffer::AppendVBO(VBOType bufferType, GLfloat* data, GLsizeiptr bufferSize, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[bufferType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, bufferSize, data);
}

void Buffer::AppendVBO(VBOType bufferType, GLint* data, GLsizeiptr bufferSize, GLuint offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[bufferType]);
	glBufferSubData(GL_ARRAY_BUFFER, offset, bufferSize, data);
}

void Buffer::AppendEBO(GLuint* data, GLsizeiptr bufferSize, GLuint offset)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, bufferSize, data);
}

void Buffer::LinkEBO()
{
	glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(0);
}

void Buffer::LinkVBO(const std::string& attribute, VBOType bufferType, ComponentType componentType, DataType dataType)
{
	glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[bufferType]);
		glVertexAttribPointer(Shader::Instance()->GetAttributeID(attribute), componentType, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(Shader::Instance()->GetAttributeID(attribute));
	glBindVertexArray(0);
}

void Buffer::Render(RenderType renderType)
{
	glBindVertexArray(m_VAO);

		if (m_hasEBO)
		{
			glDrawElements(renderType, m_totalVertices, GL_UNSIGNED_INT, 0);
		}

		else
		{
			glDrawArrays(renderType, 0, m_totalVertices);
		}

	glBindVertexArray(0);
}

void Buffer::Destroy()
{
	glDeleteBuffers(TOTAL_BUFFERS, m_VBOs);
	glDeleteVertexArrays(1, &m_VAO);

	if (m_hasEBO)
	{
		glDeleteBuffers(1, &m_EBO);
	}
}