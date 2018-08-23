#include "Collision.h"

double Collision::eSpace::intersectRayPlane(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
	const glm::vec3& planeOrigin, const glm::vec3& planeNormal)
{
	double d = -glm::dot(planeNormal, planeOrigin);

	double numerator   = glm::dot(planeNormal, rayOrigin) + d;
	double denominator = glm::dot(planeNormal, rayDirection);

	// Division by zero, impossible
	// This is due to the normal and the ray being at a right angle
	if (denominator == 0)
		return -1.0f;

	return -(numerator / denominator);
}