//
// Created by Deepak Ramalingam on 1/15/22.
//

#ifndef OPENGLCUBE_OPENGLRENDERER_H
#define OPENGLCUBE_OPENGLRENDERER_H

#if defined(STANDALONE)
#include <glad.h>
#elif defined(INCLUDE_DEEPS_ENGINE_LIBRARY)
//#include <QOpenGLExtraFunctions>
//#include <glad.h>
#else
#include <glad.h>
#endif

#if defined(STANDALONE)
#include <glfw3.h>
#endif

#include <iostream>

#include "Shader.h"

namespace OpenGLRenderer {
int createEntity();
std::vector<u_int32_t> getEntities();

void initialize();
void clear();
void update(float elapsedTime = 0);

void createWindow();
void handleScroll(double xoffset, double yoffset);
void handleKeyPress(int keyCode);
void handleKeyRelease(int keyCode);
bool shouldCloseWindow();
void closeWindow();

#if defined(STANDALONE)
void processInput(GLFWwindow* window);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#endif
}  // namespace OpenGLRenderer

#endif  // OPENGLCUBE_OPENGLRENDERER_H
