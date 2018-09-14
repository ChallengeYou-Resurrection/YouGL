#include "PlayerMovement.h"

void PlayerMovement::input(const Controller & controller, const Transform& camTransform)
{
	float speed = 0.1f;

	p_acceleration = glm::vec3(0, 0, 0); //glm::vec3(0, -9.81 * speed, 0);
										 //m_velocity = glm::vec3(0,0,0);

	if (controller.forwardPressed()) {
		p_acceleration.x += -glm::cos(glm::radians(camTransform.rotation.y + 90)) * speed;
		p_acceleration.z += -glm::sin(glm::radians(camTransform.rotation.y + 90)) * speed;
	}
	if (controller.backPressed()) {
		p_acceleration.x += glm::cos(glm::radians(camTransform.rotation.y + 90)) * speed;
		p_acceleration.z += glm::sin(glm::radians(camTransform.rotation.y + 90)) * speed;
	}
	if (controller.leftPressed()) {
		p_acceleration.x += -glm::cos(glm::radians(camTransform.rotation.y)) * speed;
		p_acceleration.z += -glm::sin(glm::radians(camTransform.rotation.y)) * speed;
	}
	if (controller.rightPressed()) {
		p_acceleration.x += glm::cos(glm::radians(camTransform.rotation.y)) * speed;
		p_acceleration.z += glm::sin(glm::radians(camTransform.rotation.y)) * speed;
	}
	if (controller.jumpPressed() && p_timeOnGround.getElapsedTime().asMilliseconds() > 450) {
		//p_acceleration.y += speed * 3.f;
		if (playerOnGround && p_acceleration.y < 0.1f)
			p_acceleration.y = 0.4f;
	}
	if (controller.downPressed()) {
		p_acceleration.y -= speed;
	}

	p_velocity += p_acceleration;
	p_velocity.x *= 0.85f;
	p_velocity.y *= 0.97f;
	p_velocity.z *= 0.85f;

	if (fabs(p_velocity.x) < 0.0001f) p_velocity.x = 0.f;
	if (fabs(p_velocity.y) < 0.0001f) p_velocity.y = 0.f;
	if (fabs(p_velocity.z) < 0.0001f) p_velocity.z = 0.f;

}

glm::vec3 PlayerMovement::movePlayer(const glm::vec3& initialPosition, float dt, DebugLogGUI& d_gui, GeoOctree& octr)
{
	glm::vec3 player_movement;
	player_movement = dt * p_velocity;

	glm::vec3 playerCentre = initialPosition - glm::vec3(0, 0.1f, 0);
	glm::vec3 m_startPosition = Coordinate::WorldToLevel(playerCentre);
	glm::vec3 m_endPosition = Coordinate::WorldToLevel(playerCentre + player_movement);

	// TODO: Get all node data that intersects with the swept sphere
	std::vector<std::shared_ptr<CYGeneric>> wall_list = octr.getCollisionMeshAtPoint(m_startPosition);

	// Insert more walls 
	if (!octr.checkIfTwoPointsInSameOctree(m_startPosition, m_endPosition))
	{
		std::vector<std::shared_ptr<CYGeneric>> extended_wall_list = octr.getCollisionMeshAtPoint(m_endPosition);
		wall_list.insert(wall_list.end(), extended_wall_list.begin(), extended_wall_list.end());
	}

	// Initialize 
	Collision::eSpace::P_CollisionPacket c_pkg;

	c_pkg.playerRadius = glm::vec3(1.f, 2.f, 1.f); // Player Size

	c_pkg.R3Position = m_startPosition;
	c_pkg.R3Velocity = player_movement;

	glm::vec3 e_velocity = Collision::eSpace::covertToESpace(c_pkg.R3Velocity, c_pkg.playerRadius);
	glm::vec3 e_origin = Collision::eSpace::covertToESpace(c_pkg.R3Position, c_pkg.playerRadius);
	c_pkg.e_velocityN = glm::normalize(c_pkg.e_velocity);

	glm::vec3 finalPos = Collision::eSpace::collideWithWorld(wall_list, &c_pkg, e_origin, e_velocity, 0);

	// New player position
	glm::vec3 r3final = c_pkg.playerRadius * finalPos;

	// Additional collision check for gravitational pull
	c_pkg.R3Position = r3final;
	c_pkg.R3Velocity = glm::vec3(0, -0.981 * 2 * dt, 0);

	e_velocity = Collision::eSpace::covertToESpace(c_pkg.R3Velocity, c_pkg.playerRadius);
	e_origin = Collision::eSpace::covertToESpace(c_pkg.R3Position, c_pkg.playerRadius);
	c_pkg.e_velocityN = glm::normalize(c_pkg.e_velocity);
	finalPos = Collision::eSpace::collideWithWorld(wall_list, &c_pkg, e_origin, e_velocity, 0);
	r3final = c_pkg.playerRadius * finalPos;

	// Check if the player is on the ground so that they can jump
	if (c_pkg.foundCollision && (player_movement.y > -0.981*dt)) {
		playerOnGround = true;
		d_gui.addMessage("On the ground");
	}
	else {
		if (playerOnGround) p_timeOnGround.restart();

		playerOnGround = false;
		d_gui.addMessage("Airbourne");
	}

	// Return the new position of the player in terms of velocity from initial point
	player_movement = r3final - m_startPosition;
	return player_movement;
}