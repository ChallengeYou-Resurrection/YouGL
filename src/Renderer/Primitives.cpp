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
			// extra indices for proper wireframe
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

	Model createSphere(glm::vec3 origin, float radius, GLint textureID, GLenum mode)
	{
		Mesh sphereMesh;
		Model modelSphere;

		unsigned int index = 0;

		auto createVertex = [&](Mesh& m, int a, int b)
		{
			// Create vertex
			m.vertices.push_back(radius * sin((a) / 180.f * M_PI) * sin((b) / 180.f * M_PI) - origin.x);
			m.vertices.push_back(radius * cos((a) / 180.f * M_PI) * sin((b) / 180.f * M_PI) + origin.y);
			m.vertices.push_back(radius * cos((b) / 180.f * M_PI) - origin.z);

			// Unnecessary info 
			m.texCoords.insert(m.texCoords.end(), { 0.0f, 0.0f, 1.0f });
			m.normals.insert(m.normals.end(), { 1.0f, 0.0f, 0.0f });
			m.colour.insert(m.colour.end(), { 1.0f, 0.0f, 0.0f });
		};
	
		for (int b = 0; b <= 180 - sphereSpace; b += sphereSpace)
		{
			for (int a = 0; a <= 360 - sphereSpace; a += sphereSpace)
			{
				createVertex(sphereMesh, a,				  b);
				createVertex(sphereMesh, a + sphereSpace, b);
				createVertex(sphereMesh, a,				  b + sphereSpace);
				createVertex(sphereMesh, a + sphereSpace, b + sphereSpace);

				sphereMesh.indices.insert(sphereMesh.indices.end(), { index + 2, index + 3, index + 1,
					index + 0 });
				index += 4;
			}
		}

		modelSphere.create(sphereMesh, textureID);
		modelSphere.setMode(mode);

		return std::move(modelSphere);
	}
}