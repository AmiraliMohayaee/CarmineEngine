#include "Light.h"
#include "Shader.h"
#include "Input.h"
#include <gtc/matrix_transform.hpp>

Light::Light(GLfloat x, GLfloat y, GLfloat z)
{
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
}

void Light::Create()
{
	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
	GLfloat color[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_buffer.Create(1, false);

	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices));
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, color, sizeof(color));
}

void Light::Draw(const Shader& shader)
{
	Buffer::SetPointSize(5.0f);
	
	shader.SendData("isLit", false);
	shader.SendData("isTextured", false);
	shader.SendData("model", m_transform.GetMatrix());

	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"), Buffer::VERTEX_BUFFER, Buffer::XYZ);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"), Buffer::COLOR_BUFFER, Buffer::RGBA);
	
	m_buffer.Render(Buffer::POINTS);

	LightMovementControl(0.1f);
}

void Light::SendToShader(const Shader& shader)
{
	shader.SendData("light.ambient", m_ambient);
	shader.SendData("light.diffuse", m_diffuse);
	shader.SendData("light.specular", m_specular);
	shader.SendData("light.position", m_transform.GetPosition());
}

void Light::Destroy()
{
	m_buffer.Destroy();
}



void Light::LightMovementControl(float cameraMoveSpeed)
{
	//Key press motions for movement
	/*if (Input::Instance()->KeyPressed() == true)
	{
		if (Input::Instance()->GetKeyPressed() == KEY_UP)
		{
			m_position += cameraMoveSpeed * m_forward;
		}
		if (Input::Instance()->GetKeyPressed() == KEY_LEFT)
		{
			m_position -= (glm::normalize(glm::cross(m_forward, m_up)) * cameraMoveSpeed);

		}
		if (Input::Instance()->GetKeyPressed() == KEY_DOWN)
		{
			m_position -= cameraMoveSpeed * m_forward;
		}
		if (Input::Instance()->GetKeyPressed() == KEY_RIGHT)
		{
			m_position += (glm::normalize(glm::cross(m_forward, m_up)) * cameraMoveSpeed);
		}

		if (Input::Instance()->GetKeyPressed() == KEY_L)
		{
			m_position.y -= cameraMoveSpeed;
		}

		if (Input::Instance()->GetKeyPressed() == KEY_P)
		{
			m_position.y += cameraMoveSpeed;
		}
	}
	else
	{
		Input::Instance()->KeyReleased();
	}*/
}