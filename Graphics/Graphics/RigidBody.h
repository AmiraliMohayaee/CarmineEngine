#pragma once


#include "glad.h"
#include <gtc/matrix_transform.hpp>


class RigidBody
{
public:

	RigidBody();
	void Update();

	void SetVel(const glm::vec3& vel);
	void SetVel(GLfloat x, GLfloat y, GLfloat z);
	void SetPos(const glm::vec3& pos);
	void SetPos(GLfloat x, GLfloat y, GLfloat z);
	void SetAcc(const glm::vec3& acc);
	void SetAcc(GLfloat x, GLfloat y, GLfloat z);
	void SetForce(const glm::vec3& force);
	void SetForce(GLfloat x, GLfloat y, GLfloat z);
	void SetMass(GLfloat mass);

	void AddForce(const glm::vec3& addForce);
	void AddForce(GLfloat x, GLfloat y, GLfloat z);

	const glm::vec3& GetVel();
	const glm::vec3& GetPos();
	const glm::vec3& GetAcc();
	const glm::vec3& GetForce();


private:

	float m_mass;

	glm::vec3 m_vel;
	glm::vec3 m_pos;
	glm::vec3 m_acc;
	glm::vec3 m_force;

};

