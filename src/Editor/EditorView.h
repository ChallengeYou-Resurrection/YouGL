#pragma once

#include <SFML/System.hpp>

#include <iostream>
#include "..\Renderer\Camera.h"
#include "..\Input\Controller.h"
#include "..\Game\WorldConstants.h"
#include "..\Util\MouseRay.h"
#include "..\Editor\GeoOctree.h"
#include "..\GUI\DebugLogGUI.h"

#include "..\Util\Collision.h"

enum class CameraType { FREEROAM, GRID, PLAYER };

class EditorView : public Camera
{
public:
	//EditorView();

	CameraType m_cameraState = CameraType::FREEROAM;

	virtual void input(const Controller& controller);
	virtual void update(float dt, DebugLogGUI& d_gui, u8 floor, GeoOctree& octr);

	void inputFreeroam(const Controller& controller);
	void inputGridview(const Controller& controller);
	void inputPlayer(const Controller& controller);

	void updateGridview(float dt, u8 floor);
	void updatePlayer(float dt, DebugLogGUI& d_gui, GeoOctree& octr);

private:
	// Mouse Drag
	bool m_grid_m2Down = false;
	sf::Vector2i m_grid_startPos;
	glm::vec3 m_grid_dragStartVec;

	// Mouse Rotation
	bool m_grid_m3Down = false;
	//MouseRay::Ray m_grid_startRay;
	glm::vec3 m_grid_origin;

	// Player Collsiion
	glm::vec3 p_acceleration;
	glm::vec3 p_velocity;

	bool playerOnGround = false;
	sf::Clock p_timeOnGround;
};

