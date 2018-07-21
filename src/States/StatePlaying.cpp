#include "StatePlaying.h"


namespace Benchmark
{
	constexpr int
		TheMouseReturns = 158209,
		WillyWonka = 127388,
		CYHQ = 51450,
		GrandTheftAuto = 36321,
		PenguinPixel = 145505,
		XMasCabin = 155913,
        PacMania = 255;
}

StatePlaying::StatePlaying(Game& game, Renderer& renderer)
:   StateBase   (game)
,	m_gui(renderer.getWindow())
{
    m_level.loadFromOldFormat(76953);
    //m_level.load("tmr.bcy");

	//m_level.saveLevel("tmr.bcy");

    m_level.createModels();
	//game.initRendererScene();

	renderer.initScene(m_camera);
}

// The functions are to avoid nuklear from thinking holding the 
// mouse button counts as multiple clicks.
void StatePlaying::preWindowEventPoll() { m_gui.inputStart(); }
void StatePlaying::postWindowEventPoll() { m_gui.inputFinish(); }

void StatePlaying::handleEvent(sf::Event& e)
{
	m_gui.inputHandle(e);
}

void StatePlaying::handleInput(Controller& controller)
{
    controller.tryToggleLookLock();

	m_camera.input(controller);
}

void StatePlaying::update(sf::Time deltaTime)
{
	m_gui.update();
	m_camera.update(deltaTime.asSeconds());
	

	if (!m_level.cameraCollsion(m_camera))
		m_camera.applyVelocity();
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(Renderer& renderer)
{
	m_level.renderFloors(renderer); // Draw entire level (TODO: Split up)
	renderer.draw(m_gui); // Draw GUI

	renderer.renderScene(m_camera); // Finalise render
}
