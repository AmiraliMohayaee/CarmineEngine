#include "Sphere.h"
#include <math.h>

// Ideal minimal number of stacks and sectors
// to maintain a spherical shape
const int MIN_STACK_COUNT = 2;
const int MIN_SECTOR_COUNT = 3;


Sphere::Sphere(GLfloat radius, GLuint sectors, GLuint stacks, GLfloat r,
	GLfloat g, GLfloat b, GLfloat alpha)
{
	m_dimension = glm::vec3(1.0f);
	m_radius = radius;
	m_stacks = stacks;
	m_sectors = sectors;
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = alpha;
}

Sphere::~Sphere()
{

}

void Sphere::SetRadius(GLfloat radius)
{
	m_radius = radius;
}

void Sphere::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = alpha;
}

void Sphere::SetSectorCount(GLint sectors)
{
	m_sectors = sectors;
}

void Sphere::SetStackCount(GLint stacks)
{
	m_stacks = stacks;
}

GLfloat Sphere::GetRadius() const
{
	return GLfloat();
}

GLuint Sphere::GetSectorCount() const
{
	return GLuint();
}

GLuint Sphere::GetStackCount() const
{
	return GLuint();
}

void Sphere::Create()
{
	glm::vec3 halfDimension = m_dimension * 0.5f;

	GLfloat vertices[] = { 0.0f


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

	GLfloat normals[] = { 0.0f
	};

	GLfloat UVs[] = { 0
	};

	GLuint indices[] = { 0
	};


	m_texture.GetTexture("CRATE", m_texture);

	m_material.SetMaterial("cube.mtl");

	m_buffer.Create(36, true);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices));
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors));
	m_buffer.FillVBO(Buffer::NORMAL_BUFFER, normals, sizeof(normals));
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs));
	m_buffer.FillEBO(indices, sizeof(indices));

	m_buffer.LinkEBO();
}

void Sphere::Destroy()
{
	m_buffer.Destroy();
}

void Sphere::Draw()
{
	//shader.SendData("isLit", m_isLit);
	//shader.SendData("isTextured", m_isTextured);
	//shader.SendData("model", m_transform.GetMatrix());

	//m_material.SendToShader(shader);

	//m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ);
	//m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA);
	//m_buffer.LinkVBO(shader.GetAttributeID("normalIn"), Buffer::NORMAL_BUFFER, Buffer::XYZ);
	//m_buffer.LinkVBO(shader.GetAttributeID("textureIn"), Buffer::TEXTURE_BUFFER, Buffer::UV);


	//if (m_isTextured)
	//{
	//	m_texture.Bind();
	//}

	//m_buffer.Render(Buffer::TRIANGLES);

	//if (m_isTextured)
	//{
	//	m_texture.UnBind();

	//}
}

