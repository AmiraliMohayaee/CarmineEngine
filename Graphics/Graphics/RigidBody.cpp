#include "RigidBody.h"
#include "Screen.h"


RigidBody::RigidBody()
{
    m_vel = glm::vec3(0.0f);
    m_pos = glm::vec3(0.0f);
    m_acc = glm::vec3(0.0f);
    m_force = glm::vec3(0.0f);

    m_mass = 0.0f;
}

void RigidBody::Update()
{
	// Setting up Euler integration

	// Temp variable for storing velocity and  
	// pos variable to find the new pos of  
	// the object after integration
	glm::vec3 oldPos = m_pos;
	glm::vec3 oldVel = m_vel;

	if (m_mass > 0)
	{
		m_acc = m_force / m_mass;
	}

	// Get engine ellapsed time of the game
	float deltaTime = static_cast<float>(Screen::Instance()->GetElapsedTime()) / 1000.0f;

	// Setting up 
	m_vel += m_acc * deltaTime;
	m_pos += ((oldVel + m_vel) * 0.5f) * deltaTime;
}

void RigidBody::SetVel(const glm::vec3& vel)
{
	m_vel = vel;
}

void RigidBody::SetVel(GLfloat x, GLfloat y, GLfloat z)
{
	m_vel.x = x;
	m_vel.y = y;
	m_vel.z = z;
}

void RigidBody::SetPos(const glm::vec3& pos)
{
	m_pos = pos;
}

void RigidBody::SetPos(GLfloat x, GLfloat y, GLfloat z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void RigidBody::SetAcc(const glm::vec3& acc)
{
	m_acc = acc;
}

void RigidBody::SetAcc(GLfloat x, GLfloat y, GLfloat z)
{
	m_acc.x = x;
	m_acc.y = y;
	m_acc.z = z;
}

void RigidBody::SetForce(const glm::vec3& force)
{
	m_force = force;
}

void RigidBody::SetForce(GLfloat x, GLfloat y, GLfloat z)
{
	m_force.x = x;
	m_force.y = y;
	m_force.z = z;
}

void RigidBody::SetMass(GLfloat mass)
{
	m_mass = mass;
}

void RigidBody::AddForce(const glm::vec3& addForce)
{
	m_force += addForce;
}

void RigidBody::AddForce(GLfloat x, GLfloat y, GLfloat z)
{
	m_force.x = x;
	m_force.y = y;
	m_force.z = z;
}

const glm::vec3& RigidBody::GetVel()
{
	return m_vel;
}

const glm::vec3& RigidBody::GetPos()
{
	return m_pos;
}

const glm::vec3& RigidBody::GetAcc()
{
	return m_acc;
}

const glm::vec3& RigidBody::GetForce()
{
	return m_force;
}
