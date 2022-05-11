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
#endif

#include "Shader.h"
#include "Scene.h"
#include "Renderer.h"

#if defined(STANDALONE)
class OpenGLRenderer: public Renderer {
#else
class OpenGLRenderer: public Renderer, QOpenGLExtraFunctions {
#endif
public:
    void initialize() override;
    void deinit() override;
    void clear() override;
    void update() override;

    unsigned int VBO, VAO;
    unsigned int lightVAO;
    unsigned int texture1, texture2;

    Shader* ourShader;
    Shader* lightingShader;
private:
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
};

#endif //EXAMPLE_RENDERER_H