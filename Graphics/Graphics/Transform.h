#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class Transform
{
public:

	Transform();
	void SetIdentity();

	void Translate(float x, float y, float z);
	void Translate(const glm::vec3& vec);
	void Rotate(float x, float y, float z);
	void Rotate(const glm::vec3 vec);
	void Scale(float x, float y, float z);
	void Scale(const glm::vec3& vec);

	void SetPosition(const glm::vec3& pos);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);


	const glm::vec3& GetPos();
	const glm::vec3& GetRot();
	const glm::vec3& GetScale();
	const glm::mat4& GetMatrix();



private:

	bool m_isDirty;

	glm::vec3 m_position;
	glm::vec3 m_scalar;
	glm::vec3 m_euler;
	glm::mat4 m_transform;


};

