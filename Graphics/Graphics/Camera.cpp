#include "Input.h"
#include "Shader.h"
#include "Camera.h"
#include "Screen.h"
#include <gtc\matrix_transform.hpp>


Camera::Camera()
{
	m_position = glm::vec3(0.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_lookAt = glm::vec3(0.0f, 0.0f, -1.0f);

	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);

	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_speed = 0.0f;
	m_fieldOfView = 45.0f;
}

const glm::vec3& Camera::GetPosition() const
{
	return m_position;
}

void Camera::SetSpeed(GLfloat speed)
{
	m_speed = speed;
}

void Camera::SetFieldOfView(GLfloat fieldOfView)
{
	m_fieldOfView = fieldOfView;
}

void Camera::SetPosition(const glm::vec3& position)
{
	m_position = position;
}

void Camera::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Camera::CreatePerspView()
{
	// Aquiring the aspect ration to pass alongside 
	// fov, close and far clipping range for the 
	// view frustum
	auto aspectRatio = (static_cast<GLfloat>(Screen::Instance()->GetScreenWidth()) /
		static_cast<GLfloat>(Screen::Instance()->GetScreenHeight()));

	m_projectionMatrix = glm::perspective(glm::radians(m_fieldOfView), aspectRatio, NEAR_CLIP, FAR_CLIP);
}

void Camera::CreateOrthoView(Origin2D origin)
{
	int width = Screen::Instance()->GetScreenWidth();
	int height = Screen::Instance()->GetScreenHeight();

	if (origin == Origin2D::TOP_LEFT)
	{
		m_projectionMatrix = glm::ortho(0, width, height, 0);
	}

	else
	{
		m_projectionMatrix = glm::ortho(0, width, 0, height);
	}
}

void Camera::Reset()
{
	m_position = glm::vec3(0.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_lookAt = glm::vec3(0.0f, 0.0f, -1.0f);

	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);

	m_pitch = 0.0f;
	m_yaw = -90.0f;
	m_speed = 0.0f;
	m_fieldOfView = 45.0f;

	// Set up perspective after reset otherwise it will
	// be set to orthographic by default
	CreatePerspView();
}


void Camera::SendToShader(const Shader& shader)
{
	shader.SendData("view", m_viewMatrix);
	shader.SendData("projection", m_projectionMatrix);
}