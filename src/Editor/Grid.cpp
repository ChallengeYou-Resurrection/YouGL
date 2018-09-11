#include "Grid.h"

Grid::Grid()
{
	createGridMesh(1);
	m_oldFloor = 1;
}

void Grid::changeGridSize(int gridSize)
{
}

const Model& Grid::getModel()
{
	return m_gridModel;
}

void Grid::update(u8 floor)
{
	if (floor != m_oldFloor)
	{
		createGridMesh(floor);
		m_oldFloor = floor;
	}
}

void Grid::createGridMesh(u8 floor)
{
	Mesh gridMesh;
	
	/*for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++) {
			// Create vertex
			gridMesh.vertices.insert(gridMesh.vertices.end(),
				{ (x*m_gridSize) / WORLD_SIZE, 0, (y*m_gridSize) / WORLD_SIZE });

			// Vertex info
			gridMesh.texCoords.insert(	gridMesh.texCoords.end(),	{ 0.0f, 0.0f, 1.0f });
			gridMesh.normals.insert(	gridMesh.normals.end(),		{ 0.0f, 1.0f, 0.0f });
			gridMesh.colour.insert(		gridMesh.colour.end(),		{ 0.0f, 0.0f, 0.0f });
		}
	}

	for (unsigned int x = 0; x < 10-1; x++)
	{
		// Join vertices in quads
		for (unsigned int y = 0; y < 10-1; y++) {
			gridMesh.indices.insert(gridMesh.indices.end(),
				{ (x)+(y*10), (x+1)+((y) * 10), (x)+((y+1) * 10)  });
		}
	}*/

	float height = (int)floor * WORLD_HEIGHT / WORLD_SIZE;
	unsigned int index = 0;
	for (int x = 0; x <= m_gridSquareNumber; x++)
	{
		// Create vertex
		gridMesh.vertices.insert(gridMesh.vertices.end(),
			{ (x*m_gridSize) / WORLD_SIZE, height, (0) / WORLD_SIZE,
			  (x*m_gridSize) / WORLD_SIZE, height, (m_gridSquareNumber * m_gridSize) / WORLD_SIZE });

		// Vertex info
		gridMesh.texCoords.insert(gridMesh.texCoords.end(), { 0.0f, 0.0f, 1.0f });
		gridMesh.normals.insert(gridMesh.normals.end(), { 0.0f, 1.0f, 0.0f });
		gridMesh.colour.insert(gridMesh.colour.end(), { 0.0f, 0.0f, 0.0f });

		// Vertex 2 info
		gridMesh.texCoords.insert(gridMesh.texCoords.end(), { 0.0f, 0.0f, 1.0f });
		gridMesh.normals.insert(gridMesh.normals.end(), { 0.0f, 1.0f, 0.0f });
		gridMesh.colour.insert(gridMesh.colour.end(), { 0.0f, 0.0f, 0.0f });

		gridMesh.indices.insert(gridMesh.indices.end(),
			{ index, index + 1 });
		index += 2;
	}

	for (int y = 0; y <= m_gridSquareNumber; y++)
	{
		// Create vertex
		gridMesh.vertices.insert(gridMesh.vertices.end(),
			{ 0 / WORLD_SIZE,								height, (y*m_gridSize) / WORLD_SIZE,
			(m_gridSquareNumber * m_gridSize) / WORLD_SIZE, height, (y*m_gridSize) / WORLD_SIZE });

		// Vertex info
		gridMesh.texCoords.insert(gridMesh.texCoords.end(), { 0.0f, 0.0f, 1.0f });
		gridMesh.normals.insert(gridMesh.normals.end(), { 0.0f, 1.0f, 0.0f });
		gridMesh.colour.insert(gridMesh.colour.end(), { 0.0f, 0.0f, 0.0f });

		// Vertex 2 info
		gridMesh.texCoords.insert(gridMesh.texCoords.end(), { 0.0f, 0.0f, 1.0f });
		gridMesh.normals.insert(gridMesh.normals.end(), { 0.0f, 1.0f, 0.0f });
		gridMesh.colour.insert(gridMesh.colour.end(), { 0.0f, 0.0f, 0.0f });

		gridMesh.indices.insert(gridMesh.indices.end(),
			{ index, index + 1 });
		index += 2;
	}

	// Create model from mesh
	m_gridModel.create(gridMesh);
	m_gridModel.setMode(GL_LINES);
}