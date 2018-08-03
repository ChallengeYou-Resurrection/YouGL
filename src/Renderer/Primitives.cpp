#include "Primitives.h"

namespace Primitives
{
	Model Primitives::createCube(glm::vec3 min, glm::vec3 max, GLenum mode)
	{
		Mesh cubeMesh;
		Model modelBox;

		// Vertices (Static)
		cubeMesh.vertices = {
			// front
			min.x, min.y, max.z,
			max.x, min.y, max.z,
			max.x, max.y, max.z,
			min.x, max.y, max.z,
			// back
			min.x, min.y, min.z,
			max.x, min.y, min.z,
			max.x, max.y, min.z,
			min.x, max.y, min.z
		};

		// Indices
		cubeMesh.indices = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3,

			5, 6, 2,
			6, 2, 1
		};

		// Fill in unnecessary info
		for (int i = 0; i < 8; i++)
		{
			cubeMesh.texCoords.insert(cubeMesh.texCoords.end(), { 1.0f, 1.0f });
			cubeMesh.normals.insert(cubeMesh.normals.end(), { 1.0f, 1.0f, 1.0f });
			cubeMesh.colour.insert(cubeMesh.colour.end(), { 1.0f, 0.0f, 0.0f });
		}

		modelBox.create(cubeMesh);
		modelBox.setMode(mode);

		return std::move(modelBox);
	}
}