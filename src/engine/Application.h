//
// Created by Deepak Ramalingam on 4/30/22.
//

#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#define SOL_ALL_SAFETIES_ON 1
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
private:
    Application() {}
public:
    Application(Application const&)  = delete;
    void operator=(Application const&)  = delete;
};


#endif //EDITOR_APPLICATION_H
