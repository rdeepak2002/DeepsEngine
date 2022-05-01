//
// Created by Deepak Ramalingam on 4/30/22.
//

#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#define SOL_ALL_SAFETIES_ON 1
#include "src/engine/include/sol.hpp"
#include "src/engine/scene/Scene.h"

class Application {
public:
    static Application& getInstance()
    {
        static Application instance;
        return instance;
    }
    DeepsEngine::Scene scene = {};
    void createWindow();
    void initialize();
    void createWindowAndInit();
    void update(bool clearScreen = true);
    bool shouldClose();
    void close();
    void createSampleEntities();
    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
private:
    Application() {}
    sol::state lua;
public:
    Application(Application const&)  = delete;
    void operator=(Application const&)  = delete;
};


#endif //EDITOR_APPLICATION_H
