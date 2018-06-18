#include "StatePlaying.h"

#include "../Game.h"

#include <vector>
#include <glad.h>
#include <SFML/Audio.hpp>

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"

namespace Benchmark
{
	constexpr int
		TheMouseReturns = 158209,
		WillyWonka = 127388,
		GrandTheftAuto = 36321,
		PenguinPixel = 145505,
		XMasCabin = 155913,
        PacMania = 255;
}

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
{
    m_level.loadFromOldFormat(51450);
    m_level.createModels();
	game.initRendererScene();
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
	m_level.renderFloors(renderer);
}
