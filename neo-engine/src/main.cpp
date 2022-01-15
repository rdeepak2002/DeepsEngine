//
// Created by Deepak Ramalingam on 1/15/22.
//

#include "OpenGLRenderer.h"

int main() {
    OpenGLRenderer::createWindow();
    OpenGLRenderer::initialize();

    while(!OpenGLRenderer::shouldCloseWindow()) {
//        OpenGLRenderer::clear();
        OpenGLRenderer::update();
    }

    OpenGLRenderer::closeWindow();

    return 0;
}