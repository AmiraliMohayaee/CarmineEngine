#pragma once


#include "Shader.h"
#include <gtc\matrix_transform.hpp>


class CameraBase
{
public:

	enum CameraType
	{
		TWO_DIM_CAM,
		THREE_DIM_CAM,
	};


public:

	virtual bool InitCamera(float x, float y, float z, float fov,
		float close, float far);

	virtual void SetFreeControl();
	virtual void SetObjectControl();

	virtual void CameraMouseMovement(float mouseSensitivity);
	virtual void CameraKeyboardMovement(float camMoveSpeed);

	virtual void SetViewAndProjection();
	virtual void Update();


protected:



};

