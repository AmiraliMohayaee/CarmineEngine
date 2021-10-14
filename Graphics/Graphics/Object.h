#pragma once

#include "Buffer.h"
#include "Model.h"
#include "RigidBody.h"
#include "Transform.h"
#include <gtc\matrix_transform.hpp>

class Object
{

public:

	Object();
	Object(const Transform& transform);
	virtual ~Object() = 0 {}

	virtual void Create() = 0;
	virtual void Destroy() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;

public:

	bool IsVisible();
	bool IsAlive();
	bool IsActive(); 
	bool IsTexture();
	bool IsLit();
	
	void IsVisible(bool flag);
	void IsAlive(bool flag);
	void IsActive(bool flag);
	void IsTextured(bool flag);
	void IsLit(bool flag);

public:

	Transform& GetTransform();
	void SetTransform(const Transform& transform);

protected:

	bool m_isLit;
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;
	bool m_isTextured;

	Transform m_transform;

};