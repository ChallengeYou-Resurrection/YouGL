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
{
    m_level.loadFromOldFormat(76953);
    //m_level.load("tmr.bcy");

	// Setup GUI Context
	ctx = nk_sfml_init(&renderer.getWindow());
	struct nk_font_atlas *atlas;
	nk_sfml_font_stash_begin(&atlas);
	nk_sfml_font_stash_end();

	// Initialize GUI Components
	m_gui.init(ctx);
	m_debug.init(ctx);

	//m_level.saveLevel("tmr.bcy");

    m_level.createModels();
	//game.initRendererScene();

	renderer.initScene(m_camera);
}

// The functions are to avoid nuklear from thinking holding the 
// mouse button counts as multiple clicks.
void StatePlaying::preWindowEventPoll() { m_gui.inputStart(); }
void StatePlaying::postWindowEventPoll() { m_gui.inputFinish(); }

// Handle GUI/Misc input 
void StatePlaying::handleEvent(sf::Event& e) { m_gui.inputHandle(e); }

void StatePlaying::handleInput(Controller& controller)
{
    controller.tryToggleLookLock();

	m_camera.input(controller);
}

void StatePlaying::update(sf::Time deltaTime)
{
	m_gui.update(deltaTime.asSeconds());
	m_debug.update(deltaTime.asSeconds());
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
	renderer.draw(m_debug);

	renderer.renderScene(m_camera); // Finalise render
}
