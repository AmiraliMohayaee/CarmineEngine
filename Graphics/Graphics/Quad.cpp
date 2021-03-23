#include "Quad.h"

Quad::Quad()
{
	m_modelMatrix = glm::mat4(1.0f);
	m_dimension = glm::vec3(1.0f);
}

void Quad::CreateBuffers()
{
	glm::vec3 halfDimension = m_dimension * 0.5f;

	GLfloat vertices[] = {
			-halfDimension.x, halfDimension.y, 0.0f,   
			 halfDimension.x, halfDimension.y, 0.0f,  
			 halfDimension.x, -halfDimension.y, 0.0f,   
			-halfDimension.x, -halfDimension.y, 0.0f,
	};


	// Passing in color data
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f };


	GLuint indices[] = { 0,  1,  3,  3,  1,  2 };

	// Contains UV coordinates
	// Coordinates are flipped upside down as OpenGL
	// takes in UV coords differently
	GLfloat UVs[] = { 0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
				      0.0f, 1.0f };

	m_texture.GetTexture("CRATE", m_texture);


	m_buffer.Create(6, true);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices));
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors));
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs));
	m_buffer.FillEBO(indices, sizeof(indices));

	m_buffer.LinkVBO("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ);
	m_buffer.LinkVBO("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB);
	m_buffer.LinkVBO("textureIn", Buffer::TEXTURE_BUFFER, Buffer::UV);
	m_buffer.LinkEBO();

}

void Quad::DestroyBuffer()
{
	m_buffer.Destroy();
	m_texture.Unload("CRATE");
}

void Quad::Draw()
{
	Shader::Instance()->SendUniformData("model", m_modelMatrix);
	Shader::Instance()->SendUniformData("isTextured", true);

	m_texture.Bind();
		m_buffer.Render(Buffer::TRIANGLES);
	m_texture.UnBind();
}

void Quad::Update()
{

}
