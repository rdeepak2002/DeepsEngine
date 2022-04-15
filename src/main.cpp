#if defined(STANDALONE)

#include "src/engine/renderer/Renderer.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#define SOL_ALL_SAFETIES_ON 1
#include "src/engine/include/sol.hpp"
#include <iostream>

using namespace DeepsEngine;
using std::filesystem::current_path;
using std::filesystem::exists;

sol::state lua;

void mainLoop() {
#if (!defined(EMSCRIPTEN) and !defined (DEVELOP_WEB))
    Renderer::getInstance().processInput();
#endif
    Renderer::getInstance().clear();
    float dt = Renderer::getInstance().update();

    // TODO: create separate (singleton?) class called Application which handles this stuff (and maybe physics) in the future
    for(auto entity : Renderer::getInstance().scene.GetScriptableEntities()) {
        Component::LuaScript luaScriptComponent = entity.GetComponent<Component::LuaScript>();
        sol::load_result script = lua.load_file(luaScriptComponent.scriptPath);
        script();

        if (!script.valid()) {
            Logger::Error("Invalid lua script");
        } else {
            sol::function onCreateFunc = lua["onCreate"];

            if (!entity.scriptOnCreateInvoked) {
                entity.scriptOnCreateInvoked = true;

                if (onCreateFunc) {
                    onCreateFunc(entity);
                } else {
                    Logger::Warn("No on create function in script");
                }
            }

            sol::function onUpdateFunc = lua["onUpdate"];

            if (onUpdateFunc) {
                onUpdateFunc(entity, dt);
            } else {
                Logger::Warn("No on update function in script");
            }
        }
    }
}

int main() {
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
    std::string scriptPath = current_path().append("assets").append("res").append("example-project").append("scripts").append("script.lua");
    entity.AddComponent<Component::LuaScript>(Component::LuaScript({scriptPath}));

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