#pragma once

#include "Dialog.h"

class Settings final : public Dialog
{

public:

	struct CameraSettings
	{
		bool has3DView;
		GLfloat cameraFOV{ 45.0f };
		GLfloat frustumFarClip{ 1000.0f };
		GLfloat frustumNearClip{ 0.001f };
	};

	virtual void Create() final;
	virtual void Destroy() final;
	virtual void Draw(const Shader& shader) final;
	virtual void Update() final;

	const CameraSettings& GetCameraSettings();

private:

	CameraSettings m_cameraSettings;

};