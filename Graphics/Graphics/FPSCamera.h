#pragma once

#include "Camera.h"


class FPSCamera : public Camera
{

public:

	FPSCamera();
	~FPSCamera() {}

	void IsFlying(bool flag);
	void SetSensitivity(GLfloat sensitivity);

	virtual void Create() {}
	virtual void Destroy() {}
	virtual void Draw(const Shader& shader) { }
	virtual void Update();
	void SendToShader(const Shader& shader) override;

private:

	bool m_isFlying;
	glm::vec3 m_forward;
	GLfloat m_sensitivity;

};