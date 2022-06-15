#include "Object.h"
#include "Shader.h"


Object::Object()
{
	m_isLit = false;
	m_isAlive = true;
	m_isActive = true;
	m_isVisible = true;
	m_isTextured = false;
}

Object::Object(const Transform& transform)
{
	m_isLit = false;
	m_isAlive = true;
	m_isActive = true;
	m_isVisible = true;
	m_isTextured = false;
	m_transform = transform;
}

//void Object::Draw()
//{
//	// TODO - find a way to remove the hard-coded shader variable names
//	//Shader::Instance()->SendUniformData("isLit", m_isLit);
//	//Shader::Instance()->SendUniformData("isTextured", m_isTextured);
//	//Shader::Instance()->SendUniformData("model", m_transform.GetMatrix());
//
//}


bool Object::IsVisible()
{
	return m_isVisible;
}

bool Object::IsAlive()
{
	return m_isAlive;
}

bool Object::IsActive()
{
	return m_isActive;
}

bool Object::IsTexture()
{
	return m_isTextured;
}

bool Object::IsLit()
{
	return m_isLit;
}

void Object::IsVisible(bool flag)
{
	m_isVisible = flag;
}

void Object::IsAlive(bool flag)
{
	m_isAlive = flag;
}

void Object::IsActive(bool flag)
{
	m_isActive = flag;
}

void Object::IsTextured(bool flag)
{
	m_isTextured = flag;
}

void Object::IsLit(bool flag)
{
	m_isLit = flag;
}

void Object::SetTransform(const Transform& transform)
{
	m_transform = transform;
}

Transform& Object::GetTransform()
{
	return m_transform;
}