#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <glad.h>
#include <vector>

#include "../Game/WorldTextures.h"
#include "RenderData.h"
#include "Shader/Shader.h"

class Model;
class RenderData;
class Camera;

class Renderer
{
    friend class Game;
    public:
        Renderer();

        void draw(const Model& model);
        void draw(const sf::Drawable& drawable);
		void initScene(const Camera& camera);
        void renderScene(const Camera& camera);

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
        std::vector<const RenderData* > m_renderData;

        Shader m_shader;
};