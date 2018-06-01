#include "Game.h"

#include "States/StatePlaying.h"

#include <glad.h>
#include <iostream>

Game::Game()
{
    //Init the OpenGL Context
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    m_window.create({ 1280, 720 }, "YouGL", sf::Style::Close, settings);

    m_window.setVerticalSyncEnabled(true);

    //Init GLAD after creation of context
    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL libs.\n";
        exit(-1);
    }

    if (GLVersion.major < 3) {
        std::cout << "Your system does not support the correct OpenGL Version.\n"
            << "Minimum version required: 3. Your version: " << GLVersion.major
            << "\n";
        exit(-1);
    }

    //Additional OpenGL setup things
    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

    pushState<StatePlaying>(*this);
}

//Runs the main loop
void Game::run()
{
    constexpr unsigned TPS = 30; //ticks per seconds
    const sf::Time     timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag      = sf::Time::Zero;

    //Main loop of the game
    while (m_window.isOpen() && !m_states.empty()) {
        auto& state = getCurrentState();

        //Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        //Real time update
        state.handleInput();
        state.update(elapsed);
        counter.update();

        //Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        //Render
        m_window.clear();
        state.render(m_window);
        counter.draw(m_window);
        m_window.display();


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
    sf::Event e;

    while (m_window.pollEvent(e)) {
        getCurrentState().handleEvent(e);
        switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
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
    return m_window;
}
