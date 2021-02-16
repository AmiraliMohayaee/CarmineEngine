#pragma once

#include "glad.h"


namespace GLError
{
    void APIENTRY GetGLErrorCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam);

    void GraphicsErrorCatch();
}