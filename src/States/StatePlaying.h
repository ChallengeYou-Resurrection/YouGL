#pragma once

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>
#include <vector>
#include <glad.h>
#include <SFML/Audio.hpp>

#include "../Game.h"
#include "StateBase.h"
#include "../Game/CYGameLevel.h"
#include "../Renderer/Camera.h"

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"

#include "../GUI/nuklear.h"
#include "../GUI/nuklear_sfml_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024


class Controller;
/**
    Game state for the main part of the game
*/
class StatePlaying : public StateBase
{
public:
    StatePlaying(Game& game, Renderer& renderer);

    void handleEvent(sf::Event& e) override;
    void handleInput(Controller& controller) override;
    void update(sf::Time deltaTime) override;
    void fixedUpdate(sf::Time deltaTime) override;
    void render(Renderer& renderer) override;

	// Nuklear input
	void preWindowEventPoll() override;
	void postWindowEventPoll() override;

private:
	Camera m_camera;
    CYGameLevel m_level;

	// GUI
	struct nk_context *ctx;
};
