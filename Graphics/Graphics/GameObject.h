#pragma once

#include "Buffer.h"
#include "Model.h"
#include "RigidBody.h"
#include "Transform.h"
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


public:

	void IsTextured(bool flag);
	void IsLit(bool flag);
	void IsVisible(bool flag);


protected:

	bool m_isTextuted;
	bool m_isLit;
	bool m_isVisible;


	Buffer m_buffer;
	Model m_model;
	RigidBody m_rigidBody;
	Transform m_transform;


	glm::vec3 m_position;
	glm::mat4 m_modelMatrix;

};