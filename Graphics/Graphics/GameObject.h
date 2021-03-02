#pragma once

#include "Buffer.h"
#include <gtc\matrix_transform.hpp>



class GameObject
{
public:

	GameObject();
	GameObject(float x, float y, float z);
	virtual ~GameObject() = 0 {}


	virtual bool Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual bool Create() = 0;
	virtual void Destroy() = 0;




protected:

	Buffer m_buffer;

	glm::vec3 m_position;
	
	glm::mat4 m_modelMatrix;

};