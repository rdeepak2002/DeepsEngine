#define SOL_ALL_SAFETIES_ON 1

#if defined(STANDALONE)
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include "src/engine/Application.h"
#include <iostream>

using namespace DeepsEngine;
using std::filesystem::current_path;
using std::filesystem::exists;

void createEntities() {
    // add camera entity
    Entity camera = Application::getInstance().scene.CreateEntity();
    (&camera.GetComponent<Component::Transform>())->position.z = 5.0;
    camera.AddComponent<Component::Camera>(Component::Camera({45.0f, 0.1f, 100.0f}));

    // add a single cube entity
    Entity entity = Application::getInstance().scene.CreateEntity();
    entity.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube"});
    std::string scriptPath = current_path().append("assets").append("res").append("example-project").append("scripts").append("script.lua");
    entity.AddComponent<Component::LuaScript>(Component::LuaScript({scriptPath}));
}

void mainLoop() {
    Application::getInstance().update();
}

int main() {
    Application::getInstance().createWindowAndInit();

    createEntities();

#ifdef EMSCRIPTEN
    // Define a mail loop function, that will be called as fast as possible
    emscripten_set_main_loop(&mainLoop, 0, 1);
#else
    // This is the normal C/C++ main loop
    while (!Application::getInstance().shouldClose()) {
        mainLoop();
    }
#endif

    Application::getInstance().close();

    return 0;
}

#else

#include <QApplication>
#include "src/editor/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

#endif