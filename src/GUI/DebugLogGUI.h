#pragma once

#include "BaseGUI.h"
#include <list>

const int FPS_MOVING_AVERAGE = 15;

class DebugLogGUI : public BaseGUI
{
public:
	DebugLogGUI();

	virtual void update(float deltaTime);

private:
	std::list<float> fps_avg;
};

