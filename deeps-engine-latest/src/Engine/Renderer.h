//
// Created by Deepak Ramalingam on 2/5/22.
//

#ifndef EXAMPLE_RENDERER_H
#define EXAMPLE_RENDERER_H

#if defined(STANDALONE)
#include <glad.h>
#include <glfw3.h>
#else
#include <QOpenGLExtraFunctions>
#endif

#include "Shader.h"

#if defined(STANDALONE)
class Renderer {
#else
class Renderer: protected QOpenGLExtraFunctions {
#endif
public:
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

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

#if defined(STANDALONE)
    GLFWwindow* window;
#endif
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;

    Shader* ourShader;
};


#endif //EXAMPLE_RENDERER_H