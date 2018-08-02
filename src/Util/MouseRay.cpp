#include "MouseRay.h"

namespace MouseRay {
	Ray calculateMouseRay(sf::Vector2i mouseCoordinates, sf::Vector2u screenResolution, const Camera & cam)
	{
		// Get camera matrices
		glm::mat4 projectionMatrix	= cam.getProjectionMatrix();
		glm::mat4 viewMatrix		= cam.getViewMatrix();

		// Gradually convert the mouse coordinates into a world space ray
		glm::vec2 normalizedCoords	= getNormalizedDeviceCoordinates(mouseCoordinates, screenResolution);
		glm::vec4 rayClipCoords		= glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.f, 1.f);
		glm::vec4 eyeCoords			= getEyeCoordinates(rayClipCoords, projectionMatrix);
		glm::vec3 worldCoords		= getWorldCoordinates(eyeCoords, viewMatrix);

		// Create ray and return
		return Ray(cam.getPositon(), worldCoords);
	}

	glm::vec2 getNormalizedDeviceCoordinates(sf::Vector2i mouseCoordinates,
		sf::Vector2u screenResolution)
	{
		std::cout << "Mouse: " << mouseCoordinates.x << ", " << mouseCoordinates.y << "\n";
		float x = (2.f * mouseCoordinates.x) / screenResolution.x - 1.f;
		float y = (2.f * mouseCoordinates.y) / screenResolution.y - 1.f;
		return glm::vec2(x, -y);
	}

	glm::vec4 getEyeCoordinates(glm::vec4& clipCoordinates, glm::mat4 projectionMatrix)
	{
		// Unproject the vector and then point it straight away to the camera (z as -1)
		glm::vec4 rayEye = glm::inverse(projectionMatrix) * clipCoordinates;
		rayEye = glm::vec4(rayEye.x, rayEye.y, -1.f, 0.f);

		return rayEye;
	}

	glm::vec3 getWorldCoordinates(glm::vec4& eyeCoordinates, glm::mat4 viewMatrix)
	{
		// Remove the view matrix by inverting it
		glm::vec4 rayWorld4D = glm::inverse(viewMatrix) * eyeCoordinates;

		// Convert to 3D vector & normalize it due to setting 
		glm::vec3 rayWorld3D = glm::vec3(rayWorld4D.x, rayWorld4D.y, rayWorld4D.z);
		return glm::normalize(rayWorld3D);
	}

}
