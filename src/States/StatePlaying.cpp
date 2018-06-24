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

StatePlaying::StatePlaying(Game& game, Renderer& renderer)
:   StateBase   (game)
{
    m_level.loadFromOldFormat(Benchmark::WillyWonka);
    //m_level.load("100000.CYs 100 000th Game.Haakson.bcy");

    m_level.createModels();
	game.initRendererScene();

	renderer.initScene(m_camera);
}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput(Controller& controller)
{
    controller.tryToggleLookLock();

	m_camera.input(controller);
}

void StatePlaying::update(sf::Time deltaTime)
{
	m_camera.update(deltaTime.asSeconds());
	m_camera.applyVelocity();
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(Renderer& renderer)
{
	m_level.renderFloors(renderer);

	renderer.renderScene(m_camera); //Finalise render
}
