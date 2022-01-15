//
// Created by Deepak Ramalingam on 1/15/22.
//

#ifndef OPENGLCUBE_OPENGLRENDERER_H
#define OPENGLCUBE_OPENGLRENDERER_H

#if defined(STANDALONE)
#include <glad.h>
#else
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLFunctions"
#endif

#include <glfw3.h>
#include <iostream>

namespace OpenGLRenderer {
  void initialize();
  void clear();
  void update();

  void createWindow();
  void processInput(GLFWwindow *window);
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  bool shouldCloseWindow();
  void closeWindow();
}

#endif  // OPENGLCUBE_OPENGLRENDERER_H
