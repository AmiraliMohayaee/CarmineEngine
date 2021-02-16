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
		XYZ = 3,
		RGBA = 4,
	};


	enum DataType
	{
		INT = GL_INT,
		FLOAT = GL_FLOAT,
	};

	enum VBOType
	{
		VERTEX_BUFFER,
		COLOR_BUFFER,
		TEXTURE_BUFFER,
	};

	enum DrawType
	{
		POINTS = GL_POINTS,

	};


public:

	Buffer();

	////////////////////////////////////////////////////
	////	New set of functions to streamline the 
	////	bufer functions
	////////////////////////////////////////////////////

	// Where we can 
	void CreateAndGenObjBuffers();

	void PassVertexElements(float vertexElements);
	void PassColorElements(float colorElements);
	void PassIndicies(float indicies);


	void BeginBindObjArray();
	void FinishBindObjArray();



public:

	// Generating VAOs and other buffers
	void GenerateVertexArray(GLsizei size, GLuint& target);
	void GenerateBuffer(GLsizei size, GLuint& target);
	
	// Binding buffers and VAOs
	void BindVertexArray(GLuint vertexArray);

	// An empty buffer so that it can populated later
	void CreateEmptyVBO(GLuint& bufferObj, const int size, GLuint attributeData);

	void BindVertices(GLuint& bufferObj, std::vector<GLfloat> data,
		GLuint attributeData);
	void BindVerticesWithSubdata(GLuint& bufferObj, std::vector<GLfloat> data,
		GLuint offset);

	void BindColors(GLuint& bufferObj, std::vector<GLfloat> data,
		GLuint attributeData);
	void BindColorsWithSubData(GLuint& bufferObj, std::vector<GLfloat> data,
		GLuint offset);

	void BindTextures(GLuint& bufferObj, std::vector<GLfloat> data,
		GLuint attributeData);

	void BindBufferWithDynamicDraw(GLuint& bufferObj, const int size,
		GLuint attributeData);

	void BindEBOArray(GLuint& bufferObj, std::vector<GLuint> data);
	void CloseVertexArray();


	void DisableVertexAttribute(GLuint attribute);
	void DeleteBuffer(GLuint& buffer);
	void DeleteVertexArray(GLuint& vertexArray);


private:

	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_vertexVBO;
	GLuint m_colorsVBO;
	GLuint m_textureVBO;
	GLuint m_normalVBO;

};