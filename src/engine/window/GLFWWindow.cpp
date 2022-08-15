//
// Created by Deepak Ramalingam on 5/10/22.
//

#include "GLFWWindow.h"
#include "Logger.h"
#include "Input.h"
#include "Application.h"

#if defined(STANDALONE)
void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    Application::getInstance().resizeWindow(width, height, true);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        Input::SetButtonDown(key, true);
    } else if (action == GLFW_RELEASE) {
        Input::SetButtonDown(key, false);
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!isnan(xpos) && !isnan(ypos)) {
        Input::SetMousePosition(xpos, ypos);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        Input::SetButtonDown(button, true);
    }

    if (action == GLFW_RELEASE) {
        Input::SetButtonDown(button, false);
    }
}

void glfwSetWindowSizeCallback(GLFWwindow* window, int width, int height)
{

}
#endif

void GLFWWindow::createWindow() {
#if defined(STANDALONE)
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(Application::getInstance().getWindowDimensions().first, Application::getInstance().getWindowDimensions().second, "Deeps Engine", NULL, NULL);
    if (window == nullptr) {
        Logger::Debug("Failed to create GLFW window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetWindowSizeCallback(window, glfwSetWindowSizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
}

bool GLFWWindow::shouldCloseWindow() {
#if defined(STANDALONE)
    if (window) {
        return glfwWindowShouldClose(window);
    } else {
        return true;
    }
#else
    return false;
#endif
}

void GLFWWindow::closeWindow() {
#if defined(STANDALONE) and !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
    glfwTerminate();
#endif
}

void GLFWWindow::processInput() {
#if defined(STANDALONE) and !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
    if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        int axisCount;
        const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCount);
        const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
        std::cout << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Left joystick: " << axes[0] << ", " << axes[1] << std::endl;
        std::cout << "Right joystick: " << axes[2] << std::endl;
        std::cout << "R2: " << axes[4] << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#endif
}

void GLFWWindow::swapBuffers() {
#if defined(STANDALONE)
    // glfw swap buffers
    glfwSwapBuffers(window);
#endif
}

void GLFWWindow::pollEvents() {
#if defined(STANDALONE)
    // glfw poll IO events (keys pressed/released, mouse moved etc.)
    glfwPollEvents();
#endif
}
