#include "MathUtilities.h"
#include <math.h>


float MathUtilities::DegToRad(float degree)
{
    float result = (degree / 180.0f) * PI;

    return result;
}

float MathUtilities::RadToDeg(float radian)
{
    float result = (radian / PI) * 180.0f;

    return result;
}

float MathUtilities::Clamp(float val, float min, float max)
{
    if (val > max)
    {
        val = max;
    }
    else if (val < min)
    {
        val = min;
    }
    return val;
}

const glm::vec3& MathUtilities::Clamp(glm::vec3& vec, glm::vec3& min, glm::vec3& max)
{
	if (vec.x > max.x)
	{
		vec.x = max.x;
	}
	else if (vec.y > max.y)
	{
		vec.y = max.y;
	}
	else if (vec.z > max.z)
	{
		vec.z = max.z;
	}

	if (vec.x < min.x)
	{
		vec.x = min.x;
	}
	else if (vec.y < min.y)
	{
		vec.y = min.y;
	}
	else if (vec.z < min.z)
	{
		vec.z = min.z;
	}

	return vec;
}

float MathUtilities::LineDistance(float a1, float b1, float a2, float b2)
{
	return sqrt(((a2 * a2) + (b2 * b2)) - ((a1 * a1) + (b1 * b1)));
}

float MathUtilities::LineDistance(const glm::vec3& start, const glm::vec3& dest)
{
	glm::vec3 result = start - dest;

	float sqrtResult = sqrt((result.x * result.x) +
		(result.y * result.y) +
		(result.z * result.z));

	return sqrtResult;
}

const glm::vec3& MathUtilities::CrossProduct(const glm::vec3& vec1, const glm::vec3& vec2)
{
	glm::vec3 result(((vec1.y * vec2.z) - (vec1.z * vec2.y)),
		((vec1.z * vec2.x) - (vec1.x * vec2.z)),
		((vec1.x * vec2.y) - (vec1.y * vec2.x)));

	return result;
}
