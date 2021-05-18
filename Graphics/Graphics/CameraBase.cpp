#include "CameraBase.h"
#include "Screen.h"
#include "Input.h"
#include "Debug.h"


bool CameraBase::InitCamera(float x, float y, float z, float fov, float close, float far)
{
	m_viewUniformID = Shader::Instance()->GetUniformID("view");
	m_projUniformID = Shader::Instance()->GetUniformID("projection");

	glEnableVertexAttribArray(m_viewUniformID);
	glEnableVertexAttribArray(m_projUniformID);

	m_cameraPos = glm::vec3(x, y, z);

	// Aquiring the aspect ration to pass alongside 
	// fov, close and far clipping range for the 
	// view frustum
	float aspectRatio = (static_cast<float>(Screen::Instance()->GetScreenWidth()) /
		static_cast<float>(Screen::Instance()->GetScreenHeight()));

	m_projectionMatrix = glm::perspective(glm::radians(fov),
		aspectRatio,
		close,
		far);

	Shader::Instance()->SendUniformData("projection", m_projectionMatrix);
	Shader::Instance()->SendUniformData("view", m_viewMatrix);

	return true;
}

void CameraBase::SetFreeControl()
{

}

void CameraBase::SetObjectControl()
{

}

void CameraBase::CameraMouseMovement(float mouseSensitivity)
{

}

void CameraBase::CameraKeyboardMovement(float camMoveSpeed)
{

}

void CameraBase::SetViewAndProjection()
{

}

void CameraBase::Update()
{

}
