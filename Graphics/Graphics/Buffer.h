#pragma once


#include "Shader.h"
#include <vector>



class Buffer
{
public:

	enum FlagType
	{
		TRUE = GL_TRUE,
		FALSE = GL_FALSE
	};
	
	enum BufferType
	{
		VBO = GL_ARRAY_BUFFER,
		EBO = GL_ELEMENT_ARRAY_BUFFER
	};

	enum FillType
	{
		SINGLE = GL_STATIC_DRAW,
		MULTIPLE = GL_DYNAMIC_DRAW
	};

	enum ComponentType
	{
		UV = 2,
		XY = 2,
		XYZ = 3,
		RGB = 3,
		RGBA = 4,
	};


	enum DataType
	{
		INT = GL_INT,
		FLOAT = GL_FLOAT,
		U_INT = GL_UNSIGNED_INT,
	};

	enum VBOType
	{
		VERTEX_BUFFER,
		COLOR_BUFFER,
		TEXTURE_BUFFER,
		NORMAL_BUFFER,
		TOTAL_BUFFERS
	};

	enum RenderType
	{
		POINTS = GL_POINTS,
		LINES = GL_LINES,
		TRIANGLES = GL_TRIANGLES,
	};


public:

	////////////////////////////////////////////////////
	////	New set of functions to streamline the 
	////	bufer functions
	////////////////////////////////////////////////////
	Buffer();

	void Create(GLuint totalVertices, bool hasEBO = false);

	void FillVBO(VBOType bufferType, GLfloat* data, GLsizeiptr bufferSize, FillType fillType = SINGLE);
	void FillEBO(GLuint* data, GLsizeiptr bufferSize, FillType fillType = SINGLE);

	void AppendVBO(VBOType bufferType, GLint* data, GLsizeiptr bufferSize, GLuint offset = 0);
	void AppendVBO(VBOType bufferType, GLfloat* data, GLsizeiptr bufferSize, GLuint offset = 0);
	void AppendEBO(GLuint* data, GLsizeiptr bufferSize, GLuint offset = 0);

	void LinkEBO();
	void LinkVBO(const std::string& attribute, VBOType bufferType, 
		ComponentType componentType, DataType dataType = Buffer::FLOAT);

	void Render(RenderType renderType);
	void Destroy();


private:
	bool m_hasEBO;

	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_VBOs[TOTAL_BUFFERS];
	GLuint m_totalVertices;

};