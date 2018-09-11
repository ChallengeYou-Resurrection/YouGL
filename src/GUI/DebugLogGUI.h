#pragma once

#include "../Maths/GlmCommon.h"

#include "BaseGUI.h"
#include <list>
#include <vector>
#include <sstream>

const int FPS_MOVING_AVERAGE = 15;

class DebugLogGUI : public BaseGUI
{
public:
	DebugLogGUI();
	void addMessage(const std::string& str);
	void add3DVector(const std::string& name, const glm::vec3& vec);

	virtual void update(float deltaTime);

private:
	std::list<float> fps_avg;
	std::vector<std::string> m_messages;
};

