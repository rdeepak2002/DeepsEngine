//
// Created by Deepak Ramalingam on 5/10/22.
//

#ifndef DEEPSENGINE_GLFWWINDOW_H
#define DEEPSENGINE_GLFWWINDOW_H


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

class GLFWWindow {
public:
    virtual void createWindow();
    virtual bool shouldCloseWindow();
    virtual void closeWindow();
    virtual void processInput();
    virtual void swapBuffers();
    virtual void pollEvents();
private:
#if defined(STANDALONE)
    GLFWwindow* window;
#endif
};


#endif //DEEPSENGINE_GLFWWINDOW_H
