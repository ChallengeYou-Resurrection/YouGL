#pragma once

#include "../Editor/GeoOctree.h"
#include "../GUI/DebugLogGUI.h"
#include "../Input/Controller.h"
#include "../Renderer/Transform.h"
#include "../Util/Collision.h"

// This class focuses on the collision detection & response of the player

class PlayerMovement
{
public:
	void input(const Controller& controller, const Transform& camTransform);
	glm::vec3 movePlayer(const glm::vec3& initialPosition, float dt, DebugLogGUI& d_gui, GeoOctree& octr);
private:
	// Player Vectors/Variables
	glm::vec3 p_acceleration;
	glm::vec3 p_velocity;

	bool playerOnGround = false;
	sf::Clock p_timeOnGround;
};

