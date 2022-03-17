#include <gtc\matrix_transform.hpp>
#include "FPSCamera.h"
#include "Input.h"


FPSCamera::FPSCamera()
{
	m_yaw = -90.0f;
	m_isFlying = true;
	m_sensitivity = 0.0f;
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
}

void FPSCamera::IsFlying(bool flag)
{
	m_isFlying = flag;
}

void FPSCamera::SetSensitivity(GLfloat sensitivity)
{
	m_sensitivity = sensitivity;
}

void FPSCamera::Update()
{
	//m_yaw += Input::Instance()->GetMouseMotion().x * m_sensitivity;
	//m_pitch -= Input::Instance()->GetMouseMotion().y * m_sensitivity;

	// Limiting the view limit to 90 degrees up and down
	//m_pitch = glm::clamp(m_pitch, -85.0f, 85.0f);

	//m_forward.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	//m_forward.y = glm::sin(glm::radians(m_pitch));
	//m_forward.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));

	//Key press motions for movement
	/*if (Input::Instance()->KeyPressed() == true)
	{
		if (Input::Instance()->GetKeyPressed() == KEY_W)
		{
			m_position += m_speed * m_forward;
		}

		if (Input::Instance()->GetKeyPressed() == KEY_A)
		{
			m_position -= (glm::normalize(glm::cross(m_forward, m_up)) * m_speed);
		}

		if (Input::Instance()->GetKeyPressed() == KEY_S)
		{
			m_position -= m_speed * m_forward;
		}

		if (Input::Instance()->GetKeyPressed() == KEY_D)
		{
			m_position += (glm::normalize(glm::cross(m_forward, m_up)) * m_speed);
		}

		if (Input::Instance()->GetKeyPressed() == KEY_Q && m_isFlying)
		{
			m_position.y -= m_speed;
		}

		if (Input::Instance()->GetKeyPressed() == KEY_E && m_isFlying)
		{
			m_position.y += m_speed;
		}
	}
	else
	{
		Input::Instance()->KeyReleased();
	}

	if (!m_isFlying)
	{
		m_position.y = 1.0f;
	}*/

}

void FPSCamera::SendToShader(const Shader& shader)
{
	//Building the view matrix every frame 
	m_viewMatrix = glm::lookAt(m_transform.GetPosition(), m_transform.GetPosition() + m_forward, m_up);

	Camera::SendToShader(shader);
}