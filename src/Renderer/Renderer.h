#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <glad.h>
#include <vector>

class Model;

class Renderer
{
    public:
        Renderer();

        void draw(const Model& model);
        void draw(const sf::Drawable& drawable);
        void display();

        const sf::RenderWindow& getWindow() const;
        bool pollEvent(sf::Event& event);
        void closeWindow();

    private:
        void initWindow();
        void initGL();

        void prepareSfmlDraw();
        void endSfmlDraw();

        sf::RenderWindow m_window;
        std::vector<const sf::Drawable*> m_sfDraws;

};