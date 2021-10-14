#include "Camera.h"
#include "Screen.h"
#include "Input.h"
#include "Debug.h"
#include "Shader.h"


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

Camera::~Camera()
{

}

const glm::vec3& Camera::GetCamPosition() const
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

void Camera::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Camera::SetPosition(glm::vec3 position)
{
	m_position = position;
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
		m_projectionMatrix = glm::ortho(0, width, 0, height);
	}

	else
	{
		m_projectionMatrix = glm::ortho(0, width, height, 0);
	}
}

void Camera::Reset()
{
	m_position = glm::vec3(0.0f);
	m_lookAt = glm::vec3(0, 0, -1);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);

	m_pitch = 0.0f;
	m_yaw = -90.0f;
	m_speed = 0.0f;
	m_fieldOfView = 45.0f;
}

void Camera::SendToShader()
{
	Shader::Instance()->SendUniformData("view", m_viewMatrix);
	//Shader::Instance()->SendUniformData("model", m_transform.GetMatrix());
	Shader::Instance()->SendUniformData("projection", m_projectionMatrix);
}

//void Camera::SendToShader(const Shader& shader)
//{
//	shader.SendData("view", m_viewMatrix);
//	shader.SendData("projection", m_projectionMatrix);
//}
