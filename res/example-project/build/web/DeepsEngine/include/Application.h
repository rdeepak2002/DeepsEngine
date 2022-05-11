//
// Created by Deepak Ramalingam on 4/30/22.
//

#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include "Scene.h"
#include "LuaScriptComponentSystem.h"
#include "Renderer.h"
#include "GLFWWindow.h"
#include <fstream>

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
    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
private:
    Application() {
        renderer = std::make_unique<Renderer>();
        window = std::make_unique<GLFWWindow>();
    }
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<GLFWWindow> window;
    std::vector<std::unique_ptr<ComponentSystem>> componentSystems;
    std::string projectPath;
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
