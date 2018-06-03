#include "StatePlaying.h"

#include "../Game.h"

#include <vector>
#include <glad.h>
#include <SFML/Audio.hpp>

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"

std::vector<GLfloat> vertices =
{
    0.5f,  0.5f, 0.0f,  // Top Right
    0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left
};

std::vector<GLuint> indices =
{
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
};

Mesh mesh;
Model model;

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
{
    mesh.verticies = vertices;
    mesh.indices = indices;
    model.create(mesh);
}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(sf::Time deltaTime)
{

}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(Renderer& renderer)
{
    renderer.draw(model);
}
