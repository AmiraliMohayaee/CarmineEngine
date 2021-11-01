#pragma once

#include <glm.hpp>


namespace MathUtilities
{

	const double PI = 3.14159265359;

	float DegToRad(float degree);
	float RadToDeg(float radian);

	float Clamp(float val, float min, float max);
	const glm::vec3& Clamp(glm::vec3& vec, glm::vec3& min, glm::vec3& max);
	float LineDistance(float a1, float b1, float a2, float b2);
	float LineDistance(const glm::vec3& start, const glm::vec3& dest);

	const glm::vec3& CrossProduct(const glm::vec3& vec1, const glm::vec3& vec2);

};

