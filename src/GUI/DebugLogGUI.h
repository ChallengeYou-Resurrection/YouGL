#pragma once

#include "BaseGUI.h"
#include <list>
#include <vector>

const int FPS_MOVING_AVERAGE = 15;

class DebugLogGUI : public BaseGUI
{
public:
	DebugLogGUI();
	void addMessage(const std::string& str);

	virtual void update(float deltaTime);

private:
	std::list<float> fps_avg;
	std::vector<std::string> m_messages;
};

