#pragma once


#include "StateBase.h"
#include "../CYLevel.h"

class Controller;
/**
    Game state for the main part of the game
*/
class StatePlaying : public StateBase
{
public:
    StatePlaying(Game& game);

    void handleEvent(sf::Event e) override;
    void handleInput(Controller& controller) override;
    void update(sf::Time deltaTime) override;
    void fixedUpdate(sf::Time deltaTime) override;
    void render(Renderer& renderer) override;

private:
    CYLevel m_level;
};
