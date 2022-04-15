#if defined(STANDALONE)

#include "src/engine/renderer/Renderer.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#define SOL_ALL_SAFETIES_ON 1
#include "src/engine/include/sol.hpp"

using namespace DeepsEngine;
using std::filesystem::current_path;

void mainLoop() {
#if (!defined(EMSCRIPTEN) and !defined (DEVELOP_WEB))
    Renderer::getInstance().processInput();
#endif
    Renderer::getInstance().clear();
    Renderer::getInstance().update();
}

int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::io);

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

    // define lua bindings
    lua.new_usertype<Logger>("Logger",
                             "Debug", &Logger::Debug,
                             "Warn", &Logger::Warn,
                             "Error", &Logger::Error
    );

    lua.new_usertype<Entity>("Entity",
                             "new", sol::no_constructor,
                             "GetId", &Entity::GetId,
                             "GetTransform", &Entity::GetComponent<Component::Transform>
    );

    lua.new_usertype<Component::Transform>("Transform",
                                           "position", &Component::Transform::position,
                                           "rotation", &Component::Transform::rotation,
                                           "scale", &Component::Transform::scale);

    lua.new_usertype<Component::Position>("Position",
                                          "x", &Component::Position::x,
                                          "y", &Component::Position::y,
                                          "z", &Component::Position::z);

    lua.new_usertype<Component::Rotation>("Rotation",
                                          "x", &Component::Rotation::x,
                                          "y", &Component::Rotation::y,
                                          "z", &Component::Rotation::z);

    lua.new_usertype<Component::Scale>("Scale",
                                           "x", &Component::Scale::x,
                                           "y", &Component::Scale::y,
                                           "z", &Component::Scale::z);

    std::string scriptPath = current_path().append("assets").append("res").append("example-project").append("scripts").append("script.lua");

    if (std::filesystem::exists(scriptPath)) {
        sol::load_result script = lua.load_file(scriptPath);
        script();

        if (!script.valid()) {
            Logger::Error("Issue with lua script");
        } else {
            sol::function onCreateFunc = lua["onCreate"];

            if (onCreateFunc) {
                onCreateFunc(entity);
            } else {
                Logger::Error("No update function in script");
            }
        }
    }

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