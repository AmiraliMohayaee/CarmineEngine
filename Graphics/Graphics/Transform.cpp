#include "Transform.h"
#include "MathUtilities.h"




Transform::Transform(const glm::mat4 matrix)
{
	m_isDirty = true;
	m_matrix = matrix;
	m_scale = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f);
	m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void Transform::SetIdentity()
{
	m_isDirty = true;
	m_scale = glm::vec3(1.0f);
	m_matrix = glm::mat4(1.0f);
	m_position = glm::vec3(0.0f);
	m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

glm::vec3 Transform::GetEulerAngles()
{
	return glm::degrees(glm::eulerAngles(m_rotation));
}

const glm::vec3& Transform::GetPosition()
{
	return m_position;
}

const glm::quat& Transform::GetRotation()
{
	return m_rotation;
}

const glm::vec3& Transform::GetScale()
{
	return m_scale;
}

// where the matrix itself is built and the dirty flag is not
// tipped
const glm::mat4& Transform::GetMatrix()
{
	if (m_isDirty)
	{
		m_matrix = glm::translate(glm::mat4(1.0f), m_position);
		m_matrix *= glm::mat4_cast(m_rotation);
		m_matrix = glm::scale(m_matrix, m_scale);
		m_isDirty = false;
	}

	return m_matrix;
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_position = position;
	m_isDirty = true;
}

void Transform::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	m_isDirty = true;
}

void Transform::SetRotation(const glm::quat& rotation)
{
	m_rotation = rotation;
	m_isDirty = true;
}

void Transform::SetRotation(const glm::vec3& eulerAngles)
{
	m_rotation = glm::quat(glm::radians(eulerAngles));
	m_isDirty = true;
}

void Transform::SetRotation(GLfloat angle, const glm::vec3& axis)
{
	m_rotation = glm::quat(glm::radians(angle), axis);
	m_isDirty = true;
}

void Transform::SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll)
{
	m_rotation = glm::quat(glm::radians(glm::vec3(pitch, yaw, roll)));
	m_isDirty = true;
}

void Transform::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
	m_isDirty = true;
}

void Transform::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
	m_isDirty = true;
}

void Transform::Translate(const glm::vec3& translation, Space space)
{
	Translate(translation.x, translation.y, translation.z, space);
}

void Transform::Translate(GLfloat x, GLfloat y, GLfloat z, Space space)
{
	if (space == Space::LOCAL)
	{
		m_position += glm::vec3(m_matrix * glm::vec4(x, y, z, 0.0f));
	}

	else
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
	}

	m_isDirty = true;
}

void Transform::Rotate(const glm::quat& rotation, Space space)
{
	glm::quat tempRotation = rotation;

	if (space == Space::LOCAL)
	{
		m_rotation = m_rotation * tempRotation;
	}

	else
	{
		m_rotation = tempRotation * m_rotation;
	}

	m_isDirty = true;
}

void Transform::Rotate(const glm::vec3& eulerAngles, Space space)
{
	Rotate(glm::quat(glm::radians(eulerAngles)), space);
}

void Transform::Rotate(GLfloat angle, const glm::vec3& axis, Space space)
{
	Rotate(glm::quat(glm::radians(angle), axis), space);
}

void Transform::Rotate(GLfloat pitch, GLfloat yaw, GLfloat roll, Space space)
{
	Rotate(glm::quat(glm::radians(glm::vec3(pitch, yaw, roll))), space);
}

void Transform::Scale(const glm::vec3& scale)
{
	m_scale *= scale;
	m_isDirty = true;
}

void Transform::Scale(GLfloat x, GLfloat y, GLfloat z)
{
	m_scale.x *= x;
	m_scale.y *= y;
	m_scale.z *= z;
	m_isDirty = true;
}
