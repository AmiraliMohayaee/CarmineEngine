#pragma once

#include "Buffer.h"
#include "Model.h"
#include "RigidBody.h"
#include "Shader.h"
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
	virtual void Draw(const Shader& shader) = 0;
	virtual void Update() = 0;
	virtual void SendToShader(const Shader& shader) {}

	void IsLit(bool flag);
	void IsAlive(bool flag);
	void IsActive(bool flag);
	void IsVisible(bool flag);
	void IsTextured(bool flag);

public:

	Transform& GetTransform();

	void SetPriority(GLuint priority);
	void SetTag(const std::string& tag);

	virtual void Render(Shader& shader) = 0;
	virtual void Update(GLfloat deltaTime) = 0;
	virtual void SendToShader(Shader& shader) = 0;

protected:

	bool m_isLit;
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;
	bool m_isTextured;

	Object* m_parent;
	std::string m_tag;
	glm::vec4 m_color;
	GLuint m_priority;
	Transform m_transform;
	glm::mat3 m_normalMatrix;

};