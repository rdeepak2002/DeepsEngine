#if defined(STANDALONE)

#include "src/engine/renderer/Renderer.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include "src/engine/include/sol.hpp"

using namespace DeepsEngine;

void mainLoop() {
#if (!defined(EMSCRIPTEN) and !defined (DEVELOP_WEB))
    Renderer::getInstance().processInput();
#endif
    Renderer::getInstance().clear();
    Renderer::getInstance().update();
}

int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua.script("print('bark bark bark!')");

    // create window and initialize opengl functions
    Renderer::getInstance().createWindow();
    Renderer::getInstance().initialize();

    // add camera entity
    Entity camera = Renderer::getInstance().scene.CreateEntity();
    (&camera.GetComponent<Component::Transform>())->position.z = 5.0;
    camera.AddComponent<Component::Camera>(Component::Camera({45.0f, 0.1f, 100.0f}));

    // add a single cube entity
    Entity entity = Renderer::getInstance().scene.CreateEntity();
    entity.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube"});

#ifdef EMSCRIPTEN
    // Define a mail loop function, that will be called as fast as possible
    emscripten_set_main_loop(&mainLoop, 0, 1);
#else
    // This is the normal C/C++ main loop
    while (!Renderer::getInstance().shouldCloseWindow()) {
        mainLoop();
    }
#endif

#if (!defined(EMSCRIPTEN) and !defined (DEVELOP_WEB))
    Renderer::getInstance().closeWindow();
#endif

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