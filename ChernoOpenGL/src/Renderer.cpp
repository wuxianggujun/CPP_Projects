//
// Created by WuXiangGuJun on 2023/7/9.
//

#include "Renderer.h"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "GL_ERROR: (" << error << ") " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

