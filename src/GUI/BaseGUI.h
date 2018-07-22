#pragma once

#include <SFML/Graphics.hpp>

#include "nuklear.h"
#include "nuklear_sfml_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

class BaseGUI
{
public:
	// Define standard functions for creation and drawing
	void init(nk_context *g_ctx) { this->ctx = g_ctx; }

	// Virtual functions for every GUI
	virtual void update(float deltaTime) = 0;

protected: 
	struct nk_context *ctx;
};

