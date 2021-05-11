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
	GameObject(const Transform& transform);
	virtual ~GameObject() = 0 {}


	virtual bool Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual bool Create() = 0;
	virtual void Destroy() = 0;


public:

	void IsVisible(bool flag);
	void IsAlive(bool flag);
	void IsActive(bool flag);


public:

	const Transform& GetTransform() { return m_transform; }

	void Translate(const glm::vec3& translate, Transform::Space);

	void SetTransform(const Transform& transform);
	void SetPosition(const glm::vec3& position);
	void SetScale(const glm::vec3& scale);
	void SetRotation(const glm::quat& rotation);





protected:

	bool m_isVisible;
	bool m_isAlive;
	bool m_isActive;


	Buffer m_buffer;
	Model m_model;
	Transform m_transform;

};