#pragma once

#include "../Renderer/Camera.h"

#include "../Maths/GlmCommon.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/* Calcuates an origin and direction vector for a ray from the screen to where the mouse
 * is pointing given a mouse position and the screen resolution
 *
 * Reference : http://antongerdelan.net/opengl/raycasting.html
 */

namespace MouseRay
{
	struct Ray {
		glm::vec3 origin;
		glm::vec3 direction; // Should Normalized

		Ray(glm::vec3 origin, glm::vec3 dir)
			: origin(origin), direction(dir) {}
	};

	Ray calculateMouseRay(sf::Vector2i mouseCoordinates, sf::Vector2u screenResolution,
		const Camera& cam);

	// Functions for calculating the ray

	// Position in screen space clamped to [-1, 1]
	glm::vec2 getNormalizedDeviceCoordinates(sf::Vector2i mouseCoordinates, 
		sf::Vector2u screenResolution);

	// Invert the projection matrix
	glm::vec4 getEyeCoordinates(glm::vec4& clipCoordinates, glm::mat4 projectionMatrix);
	// Invert the view matrix & return normalized vector
	glm::vec3 getWorldCoordinates(glm::vec4& eyeCoordinates, glm::mat4 viewMatrix);
}
