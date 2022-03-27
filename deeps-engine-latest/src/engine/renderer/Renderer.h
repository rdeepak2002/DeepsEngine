//
// Created by Deepak Ramalingam on 2/5/22.
//

#ifndef EXAMPLE_RENDERER_H
#define EXAMPLE_RENDERER_H

#if !(defined(EMSCRIPTEN) or defined(DEVELOP_WEB))

#include "src/engine/include/entt.hpp"
#if defined(STANDALONE)
#include <glad.h>
#include <glfw3.h>
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
    static Renderer& getInstance()
    {
        static Renderer instance;
        return instance;
    }

    #if defined(STANDALONE)
    void createWindow();
    #endif

    void initialize();
    void clear();
    void update();

#if defined(STANDALONE)
    bool shouldCloseWindow();
    void closeWindow();
    void processInput();
#endif

#if defined(STANDALONE)
    GLFWwindow* window;
#endif
    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;

    Shader* ourShader;

    DeepsEngine::Scene scene = {};

    void (*cb)();
private:
    Renderer() {}

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

#if !defined(STANDALONE)
    QElapsedTimer timer;
#endif
};

#endif

#endif //EXAMPLE_RENDERER_H