//
// Created by Deepak Ramalingam on 2/5/22.
//

#ifndef EXAMPLE_RENDERER_H
#define EXAMPLE_RENDERER_H

#if defined(STANDALONE)
#ifdef EMSCRIPTEN
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#else
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#else
#include <QOpenGLExtraFunctions>
#include <QElapsedTimer>
#endif

#include "Shader.h"
#include "Scene.h"

#if defined(STANDALONE)
class Renderer {
#else
class Renderer: protected QOpenGLExtraFunctions {
#endif
public:
    virtual void initialize();
    virtual void deinit();
    virtual void clear();
    virtual void update();

    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO;
    unsigned int lightVAO;
    unsigned int texture1, texture2;

    Shader* ourShader;
    Shader* lightingShader;
private:
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
};

#endif //EXAMPLE_RENDERER_H