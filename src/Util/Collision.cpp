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
	return glm::vec3(vec.x / 1.f, vec.y / 1.f, vec.z / 1.f);
}
