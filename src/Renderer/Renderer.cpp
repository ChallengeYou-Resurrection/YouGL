#include "Renderer.h"

#include <iostream>
#include "Camera.h"
#include "Model.h"
#include "OpenGLErrorCheck.h"
#include "../Maths/Matrix.h"

Renderer::Renderer()
{
    initWindow();
    initGL();

    m_shader.create("StaticModel", "StaticModel");
}

void Renderer::draw(const Model& model)
{
    m_renderData.push_back(&model.getRenderData());
}

void Renderer::draw(const sf::Drawable& drawable)
{
    m_sfDraws.push_back(&drawable);
}

void Renderer::initScene(const Camera& camera)
{
	glm::mat4 model;

	model = makeModelMatrix({ { 0, 0, 0 },{ 0, 0, 0 } });

	m_shader.bind();
	m_shader.setParameter("projMatrix", camera.getProjectionMatrix());
	m_shader.setParameter("modelMatrix", model);

	// Allow for transparent textures 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::renderScene(const Camera& camera)
{
    glClearColor(0.2f, 0.2f, 0.22f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.bind();

    /*TEMP STUFF*/
    glm::mat4 view = makeViewMatrix(camera);
    /*TEMP END*/

    m_shader.setParameter("viewMatrix", view);

    //Draw OpenGL
    int drawCalls = 0;
    for (auto renderData : m_renderData) {
        renderData->bind();
        glDrawElements(renderData->getMode(), renderData->getIndicesCount(), GL_UNSIGNED_INT, 0);
        //std::cout << "Call: " << drawCalls++ << " Indices: " << renderData->getIndicesCount() << '\n';
    }

    //Draw SFML
    /*prepareSfmlDraw();
    for (auto drawable : m_sfDraws) {
        m_window.draw(*drawable);
    }

    endSfmlDraw();*/
    //Clear the draw buffers
    m_sfDraws.clear();
    m_renderData.clear();
    
    m_window.display();
}

const sf::RenderWindow& Renderer::getWindow() const
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

    //m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60);
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
    glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
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

	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
}
