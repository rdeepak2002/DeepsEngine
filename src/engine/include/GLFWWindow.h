//
// Created by Deepak Ramalingam on 5/10/22.
//

#ifndef DEEPSENGINE_GLFWWINDOW_H
#define DEEPSENGINE_GLFWWINDOW_H

#ifdef EMSCRIPTEN
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#else
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include "Window.h"

class GLFWWindow: public Window {
public:
    void createWindow() override;
    bool shouldCloseWindow() override;
    void closeWindow() override;
    void processInput() override;
    void swapBuffers() override;
    void pollEvents() override;
    void setCursorMode(DeepsEngine::Cursor::CURSOR_TYPE cursor) override;
    bool initializeDearImGui();
private:
    GLFWwindow* window;
};


#endif //DEEPSENGINE_GLFWWINDOW_H
