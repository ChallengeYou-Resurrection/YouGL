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

	m_level.initGUI(ctx);

	//m_level.saveLevel("tmr.bcy");

    m_level.createModels();
	//game.initRendererScene();

	renderer.initScene(m_camera);
}

// The functions are to avoid nuklear from thinking holding the 
// mouse button counts as multiple clicks.
void StatePlaying::preWindowEventPoll() { nk_input_begin(ctx); }
void StatePlaying::postWindowEventPoll() { nk_input_end(ctx); }

// Handle GUI/Misc input 
void StatePlaying::handleEvent(sf::Event& e) { nk_sfml_handle_event(&e); }

void StatePlaying::handleInput(Controller& controller)
{
    controller.tryToggleLookLock();

	m_camera.input(controller);
}

void StatePlaying::update(sf::Time deltaTime)
{
	m_level.update(deltaTime.asSeconds());
	m_camera.update(deltaTime.asSeconds());
	
	// TODO: Replace
	if (!m_level.cameraCollision(m_camera))
		m_camera.applyVelocity();
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(Renderer& renderer)
{
	m_level.partiallyRenderFloors(renderer); // Draw entire level (TODO: Split up)
	m_level.renderGUIs(renderer);

	renderer.renderScene(m_camera); // Finalise render
}
