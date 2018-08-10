#pragma once
#include "..\Renderer\Camera.h"
#include "..\Input\Controller.h"
#include "..\Game\WorldConstants.h"

enum class CameraType { FREEROAM, GRID, PLAYER };

class EditorView : public Camera
{
public:
	CameraType m_cameraState = CameraType::FREEROAM;

	virtual void input(const Controller& controller);
	virtual void update(float dt, u8 floor);

	void inputFreeroam(const Controller& controller);
	void inputGridview(const Controller& controller);

	void updateGridview(float dt, u8 floor);
};

