#pragma once

#include <SFML/Graphics.hpp>
class Renderer;

class FPSCounter
{
    public:
        FPSCounter();

        void update();

        void draw(Renderer& renderer);

    private:
        sf::Text m_text;
        sf::Font m_font;

        sf::Clock m_delayTimer;
        sf::Clock m_fpsTimer;

        int m_frameCount = 0;
};