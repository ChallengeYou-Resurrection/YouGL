#include "BoundingBox.h"

#include <iostream>

bool BoundingBox::checkAABB(const BoundingBox& obj)
{
	return (this->m_vecMax.x > obj.m_vecMin.x &&
		this->m_vecMin.x < obj.m_vecMax.x &&
		this->m_vecMax.y > obj.m_vecMin.y &&
		this->m_vecMin.y < obj.m_vecMax.y &&
		this->m_vecMax.z > obj.m_vecMin.z &&
		this->m_vecMin.z < obj.m_vecMax.z);
}

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
	: m_vecMin(min)
	, m_vecMax(max)
{
	// If rendering the boxes then create a model for it
	if (RENDER_BOUNDING_BOX)
	{
		Mesh cubeMesh;

		// Vertices (Static)
		cubeMesh.vertices = {
			// front
			m_vecMin.x, m_vecMin.y,  m_vecMax.z,
			m_vecMax.x, m_vecMin.y,  m_vecMax.z,
			m_vecMax.x, m_vecMax.y,  m_vecMax.z,
			m_vecMin.x, m_vecMax.y,  m_vecMax.z,
			// back
			m_vecMin.x, m_vecMin.y, m_vecMin.z,
			m_vecMax.x, m_vecMin.y, m_vecMin.z,
			m_vecMax.x, m_vecMax.y, m_vecMin.z,
			m_vecMin.x, m_vecMax.y, m_vecMin.z,
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

		m_staticBox.create(cubeMesh);
		m_staticBox.setMode(GL_LINES);
	}
}

void BoundingBox::render(Renderer& renderer)
{
	renderer.draw(m_staticBox);
}