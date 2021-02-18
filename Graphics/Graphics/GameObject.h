#pragma once

#include "Buffer.h"
#include "Shader.h"


class GameObject
{
public:

	GameObject();
	GameObject(float x, float y, float z);
	virtual ~GameObject() = 0 {}


	virtual bool Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;




protected:

	Buffer m_buffer;


};