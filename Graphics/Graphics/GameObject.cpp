#include "GameObject.h"
#include "Shader.h"


GameObject::GameObject()
{
	m_isLit = false;
	m_isAlive = true;
	m_isActive = true;
	m_isVisible = true;
	m_isTextured = false;
}

GameObject::GameObject(const Transform& transform)
{
	m_isLit = false;
	m_isAlive = true;
	m_isActive = true;
	m_isVisible = true;
	m_isTextured = false;
	m_transform = transform;
}

void GameObject::Draw()
{
	// TODO - find a way to remove the hard-coded shader variable names
	Shader::Instance()->SendUniformData("isLit", m_isLit);
	Shader::Instance()->SendUniformData("isTextured", m_isTextured);
	Shader::Instance()->SendUniformData("model", m_transform.GetMatrix());

}


bool GameObject::IsVisible()
{
	return m_isVisible;
}

bool GameObject::IsAlive()
{
	return m_isAlive;
}

bool GameObject::IsActive()
{
	return m_isActive;
}

bool GameObject::IsTexture()
{
	return m_isTextured;
}

bool GameObject::IsLit()
{
	return m_isLit;
}

void GameObject::IsVisible(bool flag)
{
	m_isVisible = flag;
}

void GameObject::IsAlive(bool flag)
{
	m_isAlive = flag;
}

void GameObject::IsActive(bool flag)
{
	m_isActive = flag;
}

void GameObject::IsTextured(bool flag)
{
	m_isTextured = flag;
}

void GameObject::IsLit(bool flag)
{
	m_isLit = flag;
}

void GameObject::SetTransform(const Transform& transform)
{
	m_transform = transform;
}

Transform& GameObject::GetTransform()
{
	return m_transform;
}

