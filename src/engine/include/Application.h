//
// Created by Deepak Ramalingam on 4/30/22.
//

#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include "Scene.h"
#include "LuaScriptComponentSystem.h"
#include "NativeScriptComponentSystem.h"
#include "OpenGLRenderer.h"
#include "GLFWWindow.h"
#include "Window.h"
#include "Renderer.h"
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);

class Application {
public:
    static Application& getInstance()
    {
        static Application instance;
        return instance;
    }
    DeepsEngine::Scene scene = {};
    void resizeWindow(unsigned int width, unsigned int height, bool update = false);
    std::pair<unsigned int, unsigned int> getWindowDimensions();
    void initialize();
    void update(bool clearScreen = true);
    bool shouldClose();
    void close();
    void clearRenderer();
    void createSampleEntities();
    std::filesystem::path getProjectPath();
    void setProjectPath(std::string projectPath);
    float getCurrentTime();
    std::unique_ptr<Renderer> renderer;
    bool playing;
    float deltaTime;
private:
    Application() {
        renderer = std::make_unique<OpenGLRenderer>();
        window = std::make_unique<GLFWWindow>();
    }
    std::unique_ptr<Window> window;
    std::vector<std::unique_ptr<ComponentSystem>> componentSystems;
    std::string projectPath;
    std::chrono::nanoseconds lag;
    std::chrono::time_point<std::chrono::high_resolution_clock> time_start;
    bool firstMouse = true;
    glm::vec2 oldMousePosition;
#if defined(WITH_EDITOR)
    QElapsedTimer timer;
#endif
public:
    void saveProject();
    void loadProject();
    Application(Application const&)  = delete;
    void operator=(Application const&)  = delete;
};


#endif //EDITOR_APPLICATION_H
