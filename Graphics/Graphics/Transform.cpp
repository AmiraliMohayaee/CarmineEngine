#include "Transform.h"
#include "MathUtilities.h"


Transform::Transform()
{
    m_isDirty = false;

    SetIdentity();
}

void Transform::SetIdentity()
{
    m_position = glm::vec3(0.0f);
    m_euler = glm::vec3(0.0f);
    m_scalar = glm::vec3(1.0f);
    m_transform = glm::mat4(1.0f);
}

void Transform::Translate(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;

	m_isDirty = true;
}

// Translating by a vector
void Transform::Translate(const glm::vec3& vec)
{
	m_position += vec;

	m_isDirty = true;
}

void Transform::Rotate(float x, float y, float z)
{
	m_euler.x += x;
	m_euler.y += y;
	m_euler.z += z;

	m_isDirty = true;
}

void Transform::Rotate(const glm::vec3 vec)
{
	m_euler += vec;

	m_isDirty = true;
}

void Transform::Scale(float x, float y, float z)
{
	m_scalar.x *= x;

	m_isDirty = true;
}

void Transform::Scale(const glm::vec3& vec)
{


	m_isDirty = true;
}

void Transform::SetPosition(const glm::vec3& pos)
{
	m_position = pos;

	m_isDirty = true;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	m_isDirty = true;
}
void Transform::SetRotation(float x, float y, float z)
{
	m_euler.x = x;
	m_euler.y = y;
	m_euler.z = z;

	m_isDirty = true;
}
void Transform::SetScale(float x, float y, float z)
{
	m_scalar.x = x;
	m_scalar.y = y;
	m_scalar.z = z;

	m_isDirty = true;
}

const glm::vec3& Transform::GetPos()
{
	return m_position;
}

const glm::vec3& Transform::GetRot()
{
	return m_euler;
}

const glm::vec3& Transform::GetScale()
{
	return m_scalar;
}

// where the matrix itself is built and the dirty flag is not
// tipped
const glm::mat4& Transform::GetMatrix()
{
	if (m_isDirty)
	{
		m_transform = glm::translate(glm::mat4(1.0f), m_position);

		m_transform = glm::rotate(m_transform, MathUtilities::DegToRad(m_euler.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_transform = glm::rotate(m_transform, MathUtilities::DegToRad(m_euler.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_transform = glm::rotate(m_transform, MathUtilities::DegToRad(m_euler.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_transform = glm::scale(m_transform, m_scalar);
	}

	return m_transform;
}