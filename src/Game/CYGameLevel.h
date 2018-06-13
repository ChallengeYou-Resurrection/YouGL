#pragma once

#include <vector>
#include "CYObjectProperties.h"
#include "CYObjects.h"
#include "../Renderer/Model.h"

class Renderer;

class CYGameLevel
{
   public:
        CYGameLevel();

        void loadFromOldFormat(int gameNumber);
        void createModels();
        void renderFloors(Renderer& renderer);

    private:
        std::vector<Model> m_floorModels;

        LevelHeader m_header;


        std::vector<Wall> m_walls;

};