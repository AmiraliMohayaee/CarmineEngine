#include "GameObject.h"


GameObject::GameObject()
{

}

GameObject::GameObject(float x, float y, float z)
{

}



void GameObject::IsTextured(bool flag)
{
	m_isTextuted = flag;
}

void GameObject::IsLit(bool flag)
{
	m_isLit = flag;
}

void GameObject::IsVisible(bool flag)
{
	m_isVisible = flag;
}


