#include "StatePlaying.h"

#include "../Game.h"

#include <vector>
#include <glad.h>
#include <SFML/Audio.hpp>

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"

#include "../CYWebParser.h"

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
{
    // Load level
    m_level = CYWebParser::loadFileFromWebsite(163404);
    m_level.serializeIntoJsonFormat("tower.cy");
}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput(Controller& controller)
{
    controller.tryToggleLookLock();
}

void StatePlaying::update(sf::Time deltaTime)
{

}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(Renderer& renderer)
{
    m_level.drawGeometry(renderer);
}
