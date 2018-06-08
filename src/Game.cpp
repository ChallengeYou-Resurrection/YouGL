#include "Game.h"



#include <glad.h>
#include <iostream>

#include "States/StatePlaying.h"
#include "Input/KeyboardController.h"

Game::Game()
{
    m_controller = std::make_unique<KeyboardController>(m_renderer.m_window);
    pushState<StatePlaying>(*this);
}

//Runs the main loop
void Game::run()
{
    constexpr unsigned TPS = 30; //ticks per seconds
    const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag      = sf::Time::Zero;

    //Main loop of the game
    while (m_renderer.getWindow().isOpen() && !m_states.empty()) {
        auto& state = getCurrentState();

        //Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        //Real time update
        state.handleInput();
        m_camera.input(*m_controller);
        state.update(elapsed);
        counter.update();
        m_camera.update(elapsed.asSeconds());

        //Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        //Render
        state.render(m_renderer);
        counter.draw(m_renderer);
        m_renderer.renderScene(m_camera); //Finalise render

        //Handle window events
        handleEvent();
        tryPop();
    }
}

//Tries to pop the current game state
void Game::tryPop()
{
    if (m_shouldPop) {
        m_shouldPop = false;
        if (m_shouldExit) {
            m_states.clear();
            return;
        }
        else if (m_shouldChageState) {
            m_shouldChageState = false;
            m_states.pop_back();
            pushState(std::move(m_change));
            return;
        }

        m_states.pop_back();
    }
}

//Handles window events, called every frame
void Game::handleEvent()
{
    sf::Event event;


    while (m_renderer.pollEvent(event)) {
        getCurrentState().handleEvent(event);
        switch (event.type) {
            case sf::Event::Closed:
                m_renderer.closeWindow();
                break;

            default:
                break;

        }
    }
}

//Returns a reference to the current game state
StateBase& Game::getCurrentState()
{
    return *m_states.back();
}

void Game::pushState(std::unique_ptr<StateBase> state)
{
    m_states.push_back(std::move(state));
}

//Flags a boolean for the game to pop state
void Game::popState()
{
    m_shouldPop = true;
}

void Game::exitGame()
{
    m_shouldPop = true;
    m_shouldExit = true;
}


//on tin
const sf::RenderWindow& Game::getWindow() const
{
    return m_renderer.getWindow();
}
