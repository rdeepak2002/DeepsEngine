//
// Created by Deepak Ramalingam on 1/15/22.
//

#include "OpenGLRenderer.h"

int main() {
  OpenGLRenderer::createWindow();
  OpenGLRenderer::initialize();

  // create a single entity for testing purposes
  OpenGLRenderer::createEntity();

  while (!OpenGLRenderer::shouldCloseWindow()) {
    OpenGLRenderer::update();
  }

  OpenGLRenderer::closeWindow();

  return 0;
}