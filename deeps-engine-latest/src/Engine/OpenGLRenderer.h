//
// Created by Deepak Ramalingam on 1/15/22.
//

#ifndef OPENGLCUBE_OPENGLRENDERER_H
#define OPENGLCUBE_OPENGLRENDERER_H

#if defined(STANDALONE)
#include <glad.h>
#elif defined(INCLUDE_DEEPS_ENGINE_LIBRARY)
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLFunctions"
#else
#include <glad.h>
#endif

#include <glfw3.h>

#include <iostream>

#include "Shader.h"

namespace OpenGLRenderer {
void initialize();
void clear();
void update();

void createWindow();
void processInput(GLFWwindow* window);
void handleInput(int characterCode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
bool shouldCloseWindow();
void closeWindow();
}  // namespace OpenGLRenderer

#endif  // OPENGLCUBE_OPENGLRENDERER_H
