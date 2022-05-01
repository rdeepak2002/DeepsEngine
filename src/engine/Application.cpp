//
// Created by Deepak Ramalingam on 4/30/22.
//

#include "Application.h"
#include "src/engine/renderer/Renderer.h"

void Application::update() {
#if defined(STANDALONE) and !defined(EMSCRIPTEN) and !defined (DEVELOP_WEB)
    Renderer::getInstance().processInput();
#endif
    Renderer::getInstance().clear();
    Renderer::getInstance().update();
}

void Application::createWindow() {
    // create window and initialize opengl functions
#if defined(STANDALONE)
    Renderer::getInstance().createWindow();
#endif
}

void Application::initialize() {
    Renderer::getInstance().initialize();
}

void Application::createWindowAndInit() {
    createWindow();
    initialize();
}

void Application::close() {
#if defined(STANDALONE) and !defined(EMSCRIPTEN) and !defined (DEVELOP_WEB)
    Renderer::getInstance().closeWindow();
#endif
}

bool Application::shouldClose() {
#if defined(STANDALONE)
    return Renderer::getInstance().shouldCloseWindow();
#endif
    return false;
}


