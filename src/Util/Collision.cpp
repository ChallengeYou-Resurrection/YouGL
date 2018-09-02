#include "Collision.h"

// Code written by Keidy from Mr-Gamemaker
bool Collision::eSpace::checkPointInTriangle(const glm::vec3 & point, const glm::vec3 & pa, 
	const glm::vec3 & pb, const glm::vec3 & pc)
{
	glm::vec3 e10 = pb - pa;
	glm::vec3 e20 = pc - pa;
	float a = glm::dot(e10, e10);
	float b = glm::dot(e10, e20);
	float c = glm::dot(e20, e20);
	float ac_bb = (a*c) - (b*b);
	glm::vec3 vp(point.x - pa.x, point.y - pa.y, point.z - pa.z);
	float d = glm::dot(vp, e10);
	float e = glm::dot(vp, e20);
	float x = (d*c) - (e*b);
	float y = (e*a) - (d*b);
	float z = x + y - ac_bb;
	return ((collision_in(z)& ~(collision_in(x) | collision_in(y))) & 0x80000000);
}

glm::vec3 Collision::eSpace::covertToESpace(const glm::vec3 & vec)
{
	return glm::vec3(vec.x / 1.f, vec.y / 4.f, vec.z / 1.f);
}

bool Collision::eSpace::getLowestRoot(float a, float b, float c, float maxR, float* newT)
{
	float determinant = b * b - 4 * a*c;

	// Check for any roots
	if (determinant < 0)
		return false;

	// If the determinant is 0, then there's only 1 root
	if (fabs(determinant) < 0.0001f)
	{
		float x = -b / (2 * a);
		if (x > 0 && x < maxR)
		{
			*newT = x;
			return true;
		}
	}

	float sDeterminant = sqrt(determinant);

	// Determine whether A is positive so we don't need to swap the values
	int aPositive = (0 < a) - (a < 0);
	float x1 = (-b + -aPositive * sDeterminant) / (2 * a);

	if (x1 > 0 && x1 < maxR)
	{
		*newT = x1;
		return true;
	}

	// If x1 is less than 0, then we'll take the larger root
	float x2 = (-b + aPositive * sDeterminant) / (2 * a);
	if (x2 > 0 && x2 < maxR)
	{
		*newT = x2;
		return true;
	}

	return false;
}