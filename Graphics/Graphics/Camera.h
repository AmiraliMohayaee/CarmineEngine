#pragma once

#include "glad.h"
#include <glm.hpp>
#include "Object.h"

class Camera : public Object
{

public:

	enum class Origin2D
	{
		TOP_LEFT,
		BOTTOM_LEFT
	};

	Camera() {}
	virtual ~Camera() {}

	const glm::vec3& GetPosition() const;

	void SetSpeed(GLfloat speed);
	void SetFieldOfView(GLfloat fieldOfView);
	void SetClippingDistance(GLfloat nearClip, GLfloat farClip);

	void SetPosition(const glm::vec3& position);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	void CreatePerspView();
	void CreateOrthoView(Origin2D origin);

	void Reset();
	void SendToShader(const Shader& shader) override;

	virtual void Create() = 0;
	virtual void Destroy() = 0;
	virtual void Draw(const Shader& shader) = 0;
	virtual void Update() = 0;

protected:

	// Angles for pitch and yaw on camera
	// rotation
	GLfloat m_yaw{ 0.0f };
	GLfloat m_pitch{ 0.0f };
	GLfloat m_speed{ 0.0f };

	GLfloat m_farClip{ 1000.0f };
	GLfloat m_nearClip{ 0.001f };
	GLfloat m_fieldOfView{ 45.0f };

	glm::vec3 m_position{ glm::vec3(0.0f) };
	glm::vec3 m_up{ glm::vec3(0.0f, 1.0f, 0.0f) };
	glm::vec3 m_lookAt{ glm::vec3(0.0f, 0.0f, -1.0f) };

	glm::mat4 m_viewMatrix{ glm::mat4(1.0f) };
	glm::mat4 m_projectionMatrix{ glm::mat4(1.0f) };

};