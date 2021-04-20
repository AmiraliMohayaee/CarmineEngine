#include "Light.h"
#include "Shader.h"

Light::Light(GLfloat x, GLfloat y, GLfloat z)
{
	m_position = glm::vec3(x, y, z);
	m_modelMatrix = glm::mat4(1.0f);

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
}

void Light::CreateBuffers()
{
	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
	GLfloat color[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_buffer.Create(1, false);
	m_buffer.LinkVBO("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkVBO("colorIn", Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices));
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, color, sizeof(color));
}

void Light::Render()
{
	Shader::Instance()->SendUniformData("isLit", false);
	Shader::Instance()->SendUniformData("isTextured", false);
	m_buffer.Render(Buffer::POINTS);
}

void Light::SendToShader()
{
	Shader::Instance()->SendUniformData("light.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	Shader::Instance()->SendUniformData("light.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	Shader::Instance()->SendUniformData("light.specular", m_specular.r, m_specular.g, m_specular.b);
	Shader::Instance()->SendUniformData("light.position", m_position.x, m_position.y, m_position.z);
}

void Light::DestroyBuffers()
{
	m_buffer.Destroy();
}