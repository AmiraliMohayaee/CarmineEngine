#include "Quad.h"
#include <vector>

Quad::Quad(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	m_dimension.x = width;
	m_dimension.y = height;
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = alpha;
}

void Quad::Create()
{
	glm::vec3 halfDimension = m_dimension * 0.5f;

	GLfloat vertices[] = {
			-halfDimension.x, halfDimension.y, 0.0f,
			 halfDimension.x, halfDimension.y, 0.0f,
			 halfDimension.x, -halfDimension.y, 0.0f,
			-halfDimension.x, -halfDimension.y, 0.0f,
	};


	// Passing in color data
	GLfloat colors[] = { m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a,
						 m_color.r, m_color.g, m_color.b, m_color.a };


	GLfloat UVs[] = { 0.0f, 1.0f,	// top left
					  1.0f, 1.0f,	// top right
					  1.0f, 0.0f,	// bottom left
					  0.0f, 0.0f }; // bottom right

	GLfloat normals[] = { 0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f };

	GLuint indices[] = { 0,  1,  3,
						 3,  1,  2 };

	// TODO - Remove hardcoded texture name
	m_texture.GetTexture("CRATE", m_texture);

	m_material.SetMaterial("Chrome");

	m_buffer.Create(6, true);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices));
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors));
	m_buffer.FillVBO(Buffer::NORMAL_BUFFER, normals, sizeof(normals));
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs));
	m_buffer.FillEBO(indices, sizeof(indices));

	m_buffer.LinkVBO("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ);
	m_buffer.LinkVBO("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB);
	m_buffer.LinkVBO("normalIn", Buffer::NORMAL_BUFFER, Buffer::XYZ);
	m_buffer.LinkVBO("textureIn", Buffer::TEXTURE_BUFFER, Buffer::UV);
	m_buffer.LinkEBO();
}

void Quad::Destroy()
{
	m_buffer.Destroy();
	m_texture.Unload("CRATE");
}

void Quad::Draw()
{
	Shader::Instance()->SendUniformData("isLit", m_isLit);
	Shader::Instance()->SendUniformData("isTextured", m_isTextured);
	Shader::Instance()->SendUniformData("model", m_transform.GetMatrix());

	m_material.SendToShader();

	if (m_isTextured)
	{
		m_texture.Bind();
	}

	m_buffer.Render(Buffer::TRIANGLES);

	if (m_isTextured)
	{
		m_texture.UnBind();
	}
}

void Quad::SetDimension(GLfloat width, GLfloat height)
{
	m_dimension.x = width;
	m_dimension.y = height;
}

void Quad::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = alpha;
}