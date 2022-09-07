//
// Created by Deepak Ramalingam on 5/10/22.
//

#include "GLFWWindow.h"
#include "Logger.h"
#include "Input.h"
#include "Application.h"

// Dear ImGui
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

bool GLFWWindow::initializeDearImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = nullptr;
    io.Fonts->AddFontDefault();
    // TODO: fix path (notice we go one out)
    // TODO: fix path (notice we go one out)
    // TODO: fix path (notice we go one out)
    std::string fontPath = std::filesystem::current_path().append("..").append("res").append("font").append("SF-Pro.ttf");
    ImFont* font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);
    Application::getInstance().renderer->setDefaultEditorFont(font);

//    std::string fontPath = std::filesystem::current_path().append("assets").append("res").append("font").append("SF-Pro.ttf");
//    ImFont* font12 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 12);
//    ImFont* font10 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 10);
//    ImFont* font14 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 14);
//    ImFont* font18 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 18);

//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    return true;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.

    // TODO: fix this causing janky issues when resizing entire window
#ifndef WITH_EDITOR
    glViewport(0, 0, width, height);
    Application::getInstance().resizeWindow(width, height, true);
#endif
    Application::getInstance().renderer->updateFrameBuffer();
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
#ifdef STANDALONE
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
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

void GLFWWindow::createWindow() {
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
    } else {
        Logger::Debug("Created GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetWindowSizeCallback(window, glfwSetWindowSizeCallback);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

//#if defined(STANDALONE) and !defined(EMSCRIPTEN)
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        Logger::Debug("Failed to initialize GLAD");
//    } else {
//        Logger::Debug("Initialized GLAD");
//    }
//#elif defined(WITH_EDITOR)
//    // have qt initialize opengl functions
//    initializeOpenGLFunctions();
//#endif

    initializeDearImGui();
}

bool GLFWWindow::shouldCloseWindow() {
    if (window) {
        return glfwWindowShouldClose(window);
    } else {
        return true;
    }
}

void GLFWWindow::closeWindow() {
#if !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
    glfwTerminate();
#endif
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GLFWWindow::processInput() {
#if !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
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
    // glfw swap buffers
    glfwSwapBuffers(window);
}

void GLFWWindow::pollEvents() {
    // glfw poll IO events (keys pressed/released, mouse moved etc.)
    glfwPollEvents();
}

void GLFWWindow::setCursorMode(DeepsEngine::Cursor::CURSOR_TYPE cursor) {
    glfwSetInputMode(window, GLFW_CURSOR, cursor);
}