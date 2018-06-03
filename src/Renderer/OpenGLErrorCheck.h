#pragma once

#include <optional>
#include <glad.h>

/*
    Provides a more detailed error

*/
void glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__) 