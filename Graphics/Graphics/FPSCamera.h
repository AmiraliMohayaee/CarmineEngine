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

private:

	bool m_isFlying;
	GLfloat m_sensitivity;

};