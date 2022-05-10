//
// Created by Deepak Ramalingam on 4/30/22.
//

#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include "Scene.h"
#include "LuaScriptComponentSystem.h"
#include "Renderer.h"
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
    void initialize();
    void update(bool clearScreen = true);
    bool shouldClose();
    void close();
    void clearRenderer();
    void createSampleEntities();
    std::filesystem::path getProjectPath();
    void setProjectPath(std::string projectPath);
    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
private:
    Application() {
        renderer = std::make_unique<Renderer>();
        componentSystems.push_back(std::make_unique<LuaScriptComponentSystem>());
    }
    std::unique_ptr<Renderer> renderer;
    std::vector<std::unique_ptr<ComponentSystem>> componentSystems;
    std::string projectPath;
public:
    void saveProject();
    void loadProject();
    Application(Application const&)  = delete;
    void operator=(Application const&)  = delete;
};


#endif //EDITOR_APPLICATION_H
