#pragma once

#include "../Maths/GlmCommon.h"

#include "../Renderer/Mesh.h"
#include "../Renderer/Model.h"
#include "../Game/WorldConstants.h"
#include "../Util/Types.h"

class Grid
{
public:
	Grid();

	void update(u8 floor);

	void changeGridSize(int gridSize);
	void createGridMesh(u8 floor);

	const Model& getModel();

private:
	int m_gridSize = 5;
	int m_gridSquareNumber = 100;

	Model m_gridModel;

	u8 m_oldFloor;
};

