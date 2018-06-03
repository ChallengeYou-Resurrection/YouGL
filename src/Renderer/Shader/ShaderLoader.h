#pragma once

#include <glad.h>
#include <string>

GLuint loadShaders(const std::string& vertexShader,
    const std::string& fragmentShader);