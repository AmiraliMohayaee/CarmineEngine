#pragma once

#include "glad.h"
#include <glm.hpp>
#include "Object.h"


const GLfloat FAR_CLIP = 1000.f;
const GLfloat NEAR_CLIP = 0.001f;

class Camera : public Object
{
public:

	enum class Origin2D
	{
		TOP_LEFT,
		BOTTOM_LEFT,
	};

	Camera();
	virtual ~Camera();

	const glm::vec3& GetCamPosition() const;

	void SetSpeed(GLfloat speed);
	void SetFieldOfView(GLfloat fieldOfView);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetPosition(glm::vec3 position);

	void CreatePerspView();
	void CreateOrthoView(Origin2D origin);

	void Reset();
	void SendToShader(const Shader& shader);

	virtual void Draw() = 0;
	virtual void Create() = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;


	//void CameraMouseMovement(GLfloat mouseSensitivity);
	//void CameraKeyboardMovement(GLfloat camMoveSpeed);

	//void SetViewAndProJ();
	//void UpdateCamera();


protected:

	// Angles for pitch and yaw on camera
	// rotation
	GLfloat m_yaw;
	GLfloat m_pitch;
	GLfloat m_speed;
	GLfloat m_fieldOfView;

	glm::vec3 m_up;
	glm::vec3 m_lookAt;
	glm::vec3 m_position;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

};