#include "Camera.h"
#include "Screen.h"
#include "Input.h"
#include "Debug.h"


Camera::Camera()
{
	// These go into the camera
	m_viewUniformID = 0;
	m_projUniformID = 0;

	m_cameraPos = glm::vec3(0, 0, 0);
	m_cameraUp = glm::vec3(0, 1, 0);
	m_cameraForward = glm::vec3(0, 0, -1);

	m_viewMatrix = glm::mat4(1.0f);

	m_projectionMatrix = glm::mat4(1.0f);

	m_pitch = 0.0f;
	m_yaw = -90.0f;
}

Camera::~Camera()
{
	glDisableVertexAttribArray(m_viewUniformID);
	glDisableVertexAttribArray(m_projUniformID);
}

bool Camera::InitCamera(float x, float y, float z, float fov, float close, float far)
{
	m_viewUniformID = Shader::Instance()->GetUniformID("view");
	m_projUniformID = Shader::Instance()->GetUniformID("projection");

	glEnableVertexAttribArray(m_viewUniformID);
	glEnableVertexAttribArray(m_projUniformID);

	m_cameraPos = glm::vec3(x, y, z);

	// Aquiring the aspect ration to pass alongside 
	// fov, close and far clipping range for the 
	// view frustum
	float aspectRatio = static_cast<float>(Screen::Instance()->GetScreenWidth() / Screen::Instance()->GetScreenHeight());
	
	m_projectionMatrix = glm::perspective(glm::radians(fov),
		aspectRatio,
		close,
		far);

	Shader::Instance()->SendUniformData("projection", m_projectionMatrix);
	Shader::Instance()->SendUniformData("view", m_viewMatrix);

	return true;
}

void Camera::CameraMouseMovement(float mouseSensitivity)
{
	// Saving the last pos temporarily for calculating offsets
	// between last and current frame
	float mouseLastPosX = static_cast<float>(Screen::Instance()->GetScreenWidth() / 2);
	float mouseLastPosY = static_cast<float>(Screen::Instance()->GetScreenHeight() / 2);

	//Debug::Log("Mouse X Last Position is: ", mouseLastPosX);
	//Debug::Log("Mouse X Last Position is: ", mouseLastPosY);

	float mouseXOffset = Input::Instance()->GetMousePosition().x - mouseLastPosX;
	float mouseYOffset = mouseLastPosY - Input::Instance()->GetMousePosition().y;
	mouseLastPosX = Input::Instance()->GetMousePosition().x;
	mouseLastPosY = Input::Instance()->GetMousePosition().y;

	//const float mouseSensitivity = 0.1f;
	mouseXOffset *= mouseSensitivity;
	mouseYOffset *= mouseSensitivity;

	m_yaw += Input::Instance()->GetMouseMotion().x;
	m_pitch -= Input::Instance()->GetMouseMotion().y;

	// Limiting the view limit to 90 degrees up
	// and down
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;


	//Debug::Log("Yaw value is: ", m_yaw);
	//Debug::Log("Pitch value is: ", m_pitch);
	
	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	direction.y = glm::sin(glm::radians(m_pitch));
	direction.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	m_cameraForward = glm::normalize(direction);
}

void Camera::CameraKeyboardMovement(float camMoveSpeed)
{
	//Key press motions for movement
	if (Input::Instance()->KeyPressed() == true)
	{
		if (Input::Instance()->GetKeyPressed() == Key_W)
		{
			m_cameraPos += camMoveSpeed * m_cameraForward;
		}
		if (Input::Instance()->GetKeyPressed() == Key_A)
		{
			m_cameraPos -= (glm::normalize(glm::cross(m_cameraForward, m_cameraUp)) * camMoveSpeed);

		}
		if (Input::Instance()->GetKeyPressed() == Key_S)
		{
			m_cameraPos -= camMoveSpeed * m_cameraForward;
		}
		if (Input::Instance()->GetKeyPressed() == Key_D)
		{
			m_cameraPos += (glm::normalize(glm::cross(m_cameraForward, m_cameraUp)) * camMoveSpeed);
		}

		if (Input::Instance()->GetKeyPressed() == Key_Q)
		{
			m_cameraPos.y -= camMoveSpeed;
		}
		if (Input::Instance()->GetKeyPressed() == Key_E)
		{
			m_cameraPos.y += camMoveSpeed;
		}
	}
	else
	{
		Input::Instance()->KeyReleased();
	}
}

void Camera::SetViewAndProJ()
{
	Shader::Instance()->SendUniformData("view", m_viewMatrix);
}

void Camera::UpdateCamera()
{
	CameraKeyboardMovement(0.3f);
	CameraMouseMovement(0.1f);

	// Sending the view matrix every frame 
	m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraForward, m_cameraUp);
	SetViewAndProJ();
}