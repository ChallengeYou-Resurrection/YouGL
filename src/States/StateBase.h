#pragma once

#include <SFML/Graphics.hpp>

#include "../Util/NonCopyable.h"

class Game;
class Renderer;
class Controller;

class StateBase : public NonCopyable
{
    public:
        StateBase(Game& game)
            : m_pGame(&game)
        {}

        virtual ~StateBase() = default;

        virtual void handleEvent(sf::Event& e) {}
        virtual void handleInput(Controller& controller) = 0;
        virtual void update(sf::Time deltaTime) {}
        virtual void fixedUpdate(sf::Time deltaTime) {}
        virtual void render(Renderer& renderer) = 0;

		// For Nuklear (needs pre/post event polling functions)
		virtual void preWindowEventPoll() {}
		virtual void postWindowEventPoll() {}

    protected:
        Game* m_pGame;
};
