#pragma once

#include "../Maths/GlmCommon.h"
#include "glm/gtx/norm.hpp"

#include "../Game/WorldConstants.h"
#include "../Editor/CYObjects/CYGeneric.h"

#include <iostream>

typedef unsigned int uint32;
#define collision_in(a) ((uint32&) a)

namespace Collision
{
	namespace eSpace
	{
		// Given coordinates, check if they are inside of the triangle
		// Code written by Keidy from Mr-Gamemaker,
		// it is included on Kasper Fauerby's collision detection paper
		bool checkPointInTriangle(const glm::vec3& point, const glm::vec3& pa,
			const glm::vec3& pb, const glm::vec3& pc);

		// Collision Detection & Response from Kasper Fauerby's tutorial
		// Link: http://www.peroxide.dk/papers/collision/collision.pdf

		struct P_CollisionPacket {
			glm::vec3 playerRadius;

			// Vectors in Real 3D Space
			glm::vec3 R3Velocity;
			glm::vec3 R3Position;

			// eSpace Vectors of movement
			glm::vec3 e_velocity;
			glm::vec3 e_velocityN;
			glm::vec3 e_origin;

			// Collision Information
			bool foundCollision = false;
			double nearestDistance = INFINITY;
			glm::vec3 collisionPoint;
		};

		void checkCollision(P_CollisionPacket* pkg, const CPolygon& c_tri);

		static const float unitsPerMeter	= 100.0f;
		glm::vec3 collideWithWorld(const std::vector<std::shared_ptr<CYGeneric>>& obj_list,
			P_CollisionPacket* pkg, const glm::vec3& pos, const glm::vec3& vel, int depth);

		glm::vec3 covertToESpace(const glm::vec3& vec, const glm::vec3& pRadius);

		bool getLowestRoot(float a, float b, float c, float maxR, float* newT);
	}
}