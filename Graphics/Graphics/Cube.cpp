#include "Cube.h"
#include "Shader.h"
#include "Input.h"

Cube::Cube(GLfloat width, GLfloat height, GLfloat depth, GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	m_dimension.x = width;
	m_dimension.y = height;
	m_dimension.z = depth;
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = alpha;
}

void Cube::SetDimension(GLfloat width, GLfloat height, GLfloat depth)
{
	m_dimension.x = width;
	m_dimension.y = height;
	m_dimension.z = depth;
}

void Cube::SetDimension(const glm::vec3& dimensions)
{
	m_dimension = dimensions;
}

void Cube::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = alpha;
}

void Cube::Create()
{
	glm::vec3 halfDimension = m_dimension * 0.5f;

	GLfloat vertices[] = { -halfDimension.x, halfDimension.y, halfDimension.z,   //0
							halfDimension.x, halfDimension.y, halfDimension.z,    //1
							halfDimension.x, -halfDimension.y, halfDimension.z,    //2
						   -halfDimension.x, -halfDimension.y, halfDimension.z,   //3   //front face

							halfDimension.x,  halfDimension.y,  -halfDimension.z,   //4
							-halfDimension.x,  halfDimension.y,  -halfDimension.z,   //5
							-halfDimension.x, -halfDimension.y, -halfDimension.z,   //6
							halfDimension.x, -halfDimension.y, -halfDimension.z,  //7    //back face

							-halfDimension.x,  halfDimension.y, -halfDimension.z,
							-halfDimension.x,  halfDimension.y,  halfDimension.z,
							-halfDimension.x, -halfDimension.y,  halfDimension.z,
							-halfDimension.x, -halfDimension.y, -halfDimension.z,   //left face

							 halfDimension.x,  halfDimension.y, halfDimension.z,
							 halfDimension.x,  halfDimension.y, -halfDimension.z,
							 halfDimension.x, -halfDimension.y, -halfDimension.z,
							 halfDimension.x, -halfDimension.y, halfDimension.z,   //right face

							 -halfDimension.x, halfDimension.y, -halfDimension.z,
							 halfDimension.x, halfDimension.y, -halfDimension.z,
							 halfDimension.x, halfDimension.y, halfDimension.z,
							 -halfDimension.x, halfDimension.y, halfDimension.z,   //top face

							-halfDimension.x,  -halfDimension.y, halfDimension.z,
							 halfDimension.x,  -halfDimension.y, halfDimension.z,
							 halfDimension.x,  -halfDimension.y, -halfDimension.z,
							-halfDimension.x, -halfDimension.y,  -halfDimension.z,   //bottom face
	};


	GLfloat colors[] = {
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,    //front face

						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,   //back face

						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,  //left face

						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,  //right face

						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,  //top face

						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a,
						m_color.r, m_color.g, m_color.b, m_color.a, //bottom face
	};

	GLfloat normals[] = { 0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f, // front face

						  0.0f, 0.0f, -1.0f,
						  0.0f, 0.0f, -1.0f,
						  0.0f, 0.0f, -1.0f,
						  0.0f, 0.0f, -1.0f, // back face

						  -1.0f, 0.0f, 0.0f,
						  -1.0f, 0.0f, 0.0f,
						  -1.0f, 0.0f, 0.0f,
						  -1.0f, 0.0f, 0.0f, // left face

						  1.0f, 0.0f, 0.0f,
						  1.0f, 0.0f, 0.0f,
						  1.0f, 0.0f, 0.0f,
						  1.0f, 0.0f, 0.0f, // right face

						  0.0f, 1.0f, 0.0f,
						  0.0f, 1.0f, 0.0f,
						  0.0f, 1.0f, 0.0f,
						  0.0f, 1.0f, 0.0f, // top face

						  0.0f, -1.0f, 0.0f,
						  0.0f, -1.0f, 0.0f,
						  0.0f, -1.0f, 0.0f,
						  0.0f, -1.0f, 0.0f, // bottom face
	};

	GLfloat UVs[] = { 0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f,	// front face

					  0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f,	// back face

					  0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f,	// left face

					  0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f,	// right face

					  0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f,	// top face

					  0.0f, 0.0f,
					  1.0f, 0.0f,
					  1.0f, 1.0f,
					  0.0f, 1.0f,	// bottom face 
	};

	GLuint indices[] = {
					0,  1,  3,  3,  1,  2,            //front face
					 4,  5,  7,  7,  5,  6,            //back face
					 8,  9,  11,  11,  9,  10,         //left face
					 12,  13,  15,  15,  13,  14,      //right face
					 16,  17,  19,  19,  17,  18,      //top face
					 20,  21,  23,  23,  21,  22       //bottom face
	};


	m_texture.GetTexture("CRATE", m_texture);

	//m_material.SetMaterial("Chrome");

	m_buffer.Create(36, true);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices));
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors));
	m_buffer.FillVBO(Buffer::NORMAL_BUFFER, normals, sizeof(normals));
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs));
	m_buffer.FillEBO(indices, sizeof(indices));

	m_buffer.LinkEBO();
}

void Cube::Destroy()
{
	m_buffer.Destroy();
}

void Cube::Draw(const Shader& shader)
{

	shader.SendData("isLit", m_isLit);
	shader.SendData("isTextured", m_isTextured);
	shader.SendData("model", m_transform.GetMatrix());

	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA);
	m_buffer.LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ);
	m_buffer.LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV);

	m_material.SendToShader(shader);

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