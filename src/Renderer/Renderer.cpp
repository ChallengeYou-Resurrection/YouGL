#include "Renderer.h"

#include <iostream>

Renderer::Renderer()
{
    initWindow();
    initGL();
}

void Renderer::draw(const sf::Drawable& drawable)
{
    m_sfDraws.push_back(&drawable);
}

void Renderer::display()
{
    m_window.clear();
    //draw opengl here

    //Draw SFML
    prepareSfmlDraw();
    for (auto drawable : m_sfDraws) {
        m_window.draw(*drawable);
    }
    

    m_window.display();
}

const sf::RenderWindow & Renderer::getWindow() const
{
    return m_window;
}

bool Renderer::pollEvent(sf::Event& event)
{
    return m_window.pollEvent(event);
}

void Renderer::closeWindow()
{
    m_window.close();
}

void Renderer::initWindow()
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
}

void Renderer::initGL()
{
    //Init GLAD after creation of context
    if (!gladLoadGL()) {
        std::cout << "Unable to load OpenGL libs.\n";
        exit(-1);
    }

    //Check version 
    if (GLVersion.major < 3) {
        std::cout << "Your system does not support the correct OpenGL Version.\n"
            << "Minimum version required: 3. Your version: " << GLVersion.major
            << "\n";
        exit(-1);
    }

    //Additional OpenGL setup things
    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);
}

void Renderer::prepareSfmlDraw()
{
    glDisable(GL_DEPTH_TEST);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glUseProgram(0);

    m_window.pushGLStates();
    m_window.resetGLStates();

}

void Renderer::endSfmlDraw()
{
    m_window.popGLStates();
}
