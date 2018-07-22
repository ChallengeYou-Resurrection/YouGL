#pragma once

#include "BaseGUI.h"
#include <iostream>

#include "../Game/WorldTextures.h"


class EditorGUI : virtual public BaseGUI
{
public:
	EditorGUI();

	void inputStart();
	void inputHandle(sf::Event& evt);
	void inputFinish();

	virtual void update(float deltaTime);

private:
	struct nk_colorf bg;
};

