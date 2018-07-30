#pragma once

#include "BaseGUI.h"
#include <iostream>
#include "../Util/Types.h"
#include "../Game/WorldTextures.h"

class EditorGUI : virtual public BaseGUI
{
public:
	EditorGUI(u8* cFloor);

	virtual void update(float deltaTime);

private:
	struct nk_colorf bg;

	u8* m_currentFloor;
};

