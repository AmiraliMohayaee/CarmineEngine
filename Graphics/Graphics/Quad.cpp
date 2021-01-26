#include "Quad.h"

Quad::Quad()
{
	m_VAO = 0;
	m_vertexVBO = 0;
	m_colorsVBO = 0;
	m_textureVBO = 0;
	m_EBO = 0;

	// Attributes
	m_vertexAttributeID = 0;
	m_colorAttributeID = 0;
	m_textureAttributeID = 0;

	// Uniforms
	m_modelUniformID = 0;

	m_modelMatrix = glm::mat4(1.0f);
}

Quad::~Quad()
{
	m_buffer.DisableVertexAttribute(m_colorAttributeID);
	m_buffer.DisableVertexAttribute(m_vertexAttributeID);
	m_buffer.DisableVertexAttribute(m_modelUniformID);
	m_buffer.DisableVertexAttribute(m_textureAttributeID);

	m_buffer.DeleteBuffer(m_vertexVBO);
	m_buffer.DeleteBuffer(m_colorsVBO);
	m_buffer.DeleteBuffer(m_textureVBO);
	m_buffer.DeleteBuffer(m_EBO);
	m_buffer.DeleteVertexArray(m_VAO);
}

void Quad::CreateBuffers()
{
	// Seperate vertex data buffer object
	m_vertexContainer = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
	};


	// Passing in color data
	m_colorContainer = {
	  0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f
	};

	// EBO indecies shared between the two triangles
	m_indiciesContainer = {     //bottom face
	};

	// Contains UV coordinates
	// Coordinates are flipped upside down as OpenGL
	// takes in UV coords differently
	m_uvContainer = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	m_texture.Load("Assets/Textures/Test.png", "CRATE");

	m_vertexAttributeID = Shader::Instance()->GetAttributeID("vertexIn");
	m_colorAttributeID = Shader::Instance()->GetAttributeID("colorIn");
	m_textureAttributeID = Shader::Instance()->GetAttributeID("textureIn");
	m_modelUniformID = Shader::Instance()->GetUniformID("model");

	Shader::Instance()->EnableVertexAttributeArray(m_vertexAttributeID);
	Shader::Instance()->EnableVertexAttributeArray(m_colorAttributeID);
	Shader::Instance()->EnableVertexAttributeArray(m_textureAttributeID);
	Shader::Instance()->EnableVertexAttributeArray(m_modelUniformID);


	m_buffer.GenerateVertexArray(1, m_VAO);
	m_buffer.GenerateBuffer(1, m_vertexVBO);
	m_buffer.GenerateBuffer(1, m_colorsVBO);
	m_buffer.GenerateBuffer(1, m_textureVBO);
	//m_buffer.GenerateBuffer(1, m_EBO);

	m_buffer.BindVertexArray(m_VAO);

		m_buffer.BindVertices(m_vertexVBO, m_vertexContainer, m_vertexAttributeID);
		m_buffer.BindColors(m_colorsVBO, m_colorContainer, m_colorAttributeID);
		m_buffer.BindTextures(m_textureVBO, m_uvContainer, m_textureAttributeID);
		//m_buffer.BindEBOArray(m_EBO, m_indiciesContainer);

	m_buffer.CloseVertexArray();
}

void Quad::Draw()
{
	Shader::Instance()->SendUniformData("model", m_modelMatrix);

	m_texture.Bind();

		m_buffer.BindVertexArray(m_VAO);

			//glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

		m_buffer.CloseVertexArray();

	m_texture.UnBind();
}

void Quad::Update()
{

}
