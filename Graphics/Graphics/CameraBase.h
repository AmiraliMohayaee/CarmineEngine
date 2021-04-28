#pragma once



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
		float close, float far) {}

	virtual void SetViewAndProjection();
	virtual void Update();


protected:



};

