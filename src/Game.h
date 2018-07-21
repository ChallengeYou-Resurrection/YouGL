#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <glad.h>
#include <iostream>

#include "States/StatePlaying.h"
#include "States/StateBase.h"
#include "Util/NonMoveable.h"
#include "Util/FPSCounter.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "GUI/NuklearContext.h"

#include "Input/Controller.h"
#include "Input/KeyboardController.h"

/**
    Main controlling class of the game.
    Handles state switches and the main loop, as well
    as counting the FPS
*/
class Game : public NonCopyable, public NonMovable
{
    public:
        Game();

        void run();

        template<typename T, typename... Args>
        void pushState(Args&&... args);
        void pushState(std::unique_ptr<StateBase> state);
        void popState();
        void exitGame();
        template<typename T, typename... Args>
        void changeState(Args&&... args);

        sf::RenderWindow& getWindow();
		void initRendererScene();

    private:
        void handleEvent();
        void tryPop();

        StateBase& getCurrentState();

        Renderer m_renderer;
		NuklearContext m_nkctx;
        std::unique_ptr<Controller> m_controller;

        std::unique_ptr<StateBase> m_change;
        std::vector<std::unique_ptr<StateBase>> m_states;

        FPSCounter counter;

        bool m_shouldPop = false;
        bool m_shouldExit = false;
        bool m_shouldChageState = false;
};

template<typename T, typename... Args>
inline void Game::pushState(Args&&... args)
{
    pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T, typename ...Args>
inline void Game::changeState(Args && ...args)
{
    m_change = std::make_unique<T>(std::forward<Args>(args)...);
    m_shouldPop = true;
    m_shouldChageState = true;
}
