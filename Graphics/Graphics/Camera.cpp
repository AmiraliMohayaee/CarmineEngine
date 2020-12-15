#include "Camera.h"
#include "Screen.h"


Camera::Camera()
{
	// These go into the camera
	m_viewUniformID = 0;
	m_projUniformID = 0;

	m_cameraPos = glm::vec3(0, 0, 0);
	m_cameraRight = glm::vec3(1, 0, 0);

	m_cameraUp = glm::vec3(0, 1, 0);
	m_cameraForward = glm::vec3(0, 0, -1);

	m_viewMatrix = glm::mat4(1.0f);

	m_projectionMatrix = glm::mat4(1.0f);
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

void Camera::SetViewAndProJ()
{
	Shader::Instance()->SendUniformData("view", m_viewMatrix);
	//Shader::Instance()->SendUniformData("projection", m_projectionMatrix);
}

void Camera::UpdateCamera()
{
	// Camera Controls


	// Sending the view matrix every frame 
	m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraForward, m_cameraUp);
	SetViewAndProJ();

}

