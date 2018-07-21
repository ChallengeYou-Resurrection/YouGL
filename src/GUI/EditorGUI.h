#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "nuklear.h"
#include "nuklear_sfml_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

class EditorGUI
{
public:
	EditorGUI(sf::RenderWindow& win);

	void inputStart();
	void inputHandle(sf::Event& evt);
	void inputFinish();

	void update();
	void render() const;

private:
	struct nk_context *ctx;
	struct nk_colorf bg;
};

