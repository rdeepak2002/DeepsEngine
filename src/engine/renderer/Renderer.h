//
// Created by Deepak Ramalingam on 2/5/22.
//

#ifndef EXAMPLE_RENDERER_H
#define EXAMPLE_RENDERER_H

#include "src/engine/include/entt.hpp"
#if defined(STANDALONE)
#ifdef EMSCRIPTEN
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#else
#include <glad.h>
#include <glfw3.h>
#endif
#else
#include <QOpenGLExtraFunctions>
#include <QElapsedTimer>
#endif

#include "Shader.h"
#include "src/engine/scene/Scene.h"

#if defined(STANDALONE)
class Renderer {
#else
class Renderer: protected QOpenGLExtraFunctions {
#endif
public:
    void createWindow();
    bool shouldCloseWindow();
    void initialize();
    void clear();
    void update();
    void closeWindow();
    void processInput();
    float getCurrentTime();

    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO;
    unsigned int lightVAO;
    unsigned int texture1, texture2;

    Shader* ourShader;
    Shader* lightingShader;

#if defined(STANDALONE)
    GLFWwindow* window;
#else
    QElapsedTimer timer;
#endif

private:
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
};

#endif //EXAMPLE_RENDERER_H