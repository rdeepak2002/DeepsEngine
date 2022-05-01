//
// Created by Deepak Ramalingam on 4/30/22.
//
#include "Application.h"
#include "src/engine/renderer/Renderer.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include <iostream>

using namespace DeepsEngine;
using std::filesystem::current_path;
using std::filesystem::exists;

void Application::update(bool clearScreen) {
//    // per-frame time logic
//    // --------------------
    float currentFrame = Renderer::getInstance().getCurrentTime();

    // calculate delta time
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    Renderer::getInstance().processInput();

    if (clearScreen) {
        Renderer::getInstance().clear();
    }

    Renderer::getInstance().update();

    // TODO: move this to script system
    for(auto entity : Application::getInstance().scene.GetScriptableEntities()) {
        auto &luaScriptComponent = entity.GetComponent<DeepsEngine::Component::LuaScript>();
        lua.script_file(luaScriptComponent.scriptPath);

        if (entity.IsValid() && luaScriptComponent.shouldInit) {
            luaScriptComponent.self = lua.create_table_with("value", "key");
            lua["self"] = luaScriptComponent.self;

            auto f = Application::getInstance().lua["init"];

            if(f.valid()) {
                f(entity);
            } else {
                Logger::Warn("Invalid init function in script");
            }

            luaScriptComponent.shouldInit = false;
        } else if (entity.IsValid() && luaScriptComponent.shouldUpdate) {
            lua["self"] = luaScriptComponent.self;

            auto f = lua["update"];

            if (f.valid()) {
                f(entity, deltaTime);
            } else {
                Logger::Warn("Invalid update function in script");
            }
        }
    }
}

void Application::createWindow() {
    Renderer::getInstance().createWindow();
}

void Application::initialize() {
    Renderer::getInstance().initialize();

    // TODO: move this to script system
    Logger::Debug("initializing script system");

    // open libraries with lua
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string, sol::lib::io);

    // define lua bindings
    lua.new_usertype<Logger>("Logger",
                             "Debug", &Logger::Debug,
                             "Warn", &Logger::Warn,
                             "Error", &Logger::Error
    );

    lua.new_usertype<DeepsEngine::Entity>("Entity",
                                          "new", sol::no_constructor,
                                          "GetId", &DeepsEngine::Entity::GetId,
                                          "GetTransform", &DeepsEngine::Entity::GetComponent<DeepsEngine::Component::Transform>
    );

    lua.new_usertype<DeepsEngine::Component::Transform>("Transform",
                                                        "position", &DeepsEngine::Component::Transform::position,
                                                        "rotation", &DeepsEngine::Component::Transform::rotation,
                                                        "scale", &DeepsEngine::Component::Transform::scale);

    lua.new_usertype<DeepsEngine::Component::Position>("Position",
                                                       "x", &DeepsEngine::Component::Position::x,
                                                       "y", &DeepsEngine::Component::Position::y,
                                                       "z", &DeepsEngine::Component::Position::z);

    lua.new_usertype<DeepsEngine::Component::Rotation>("Rotation",
                                                       "x", &DeepsEngine::Component::Rotation::x,
                                                       "y", &DeepsEngine::Component::Rotation::y,
                                                       "z", &DeepsEngine::Component::Rotation::z);

    lua.new_usertype<DeepsEngine::Component::Scale>("Scale",
                                                    "x", &DeepsEngine::Component::Scale::x,
                                                    "y", &DeepsEngine::Component::Scale::y,
                                                    "z", &DeepsEngine::Component::Scale::z);
}

void Application::createWindowAndInit() {
    createWindow();
    initialize();
}

void Application::close() {
    Renderer::getInstance().closeWindow();
}

bool Application::shouldClose() {
    return Renderer::getInstance().shouldCloseWindow();
}

void Application::createSampleEntities() {
    // add camera entity
    Entity camera = Application::getInstance().scene.CreateEntity("Main Camera");
    (&camera.GetComponent<Component::Transform>())->position.z = 5.0;
    camera.AddComponent<Component::Camera>(Component::Camera({45.0f, 0.1f, 100.0f}));

    // add a single cube entity
    Entity entity = Application::getInstance().scene.CreateEntity("Cube");
    entity.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube"});
    std::string scriptPath = current_path().append("assets").append("res").append("example-project").append("scripts").append("script.lua");
    entity.AddComponent<Component::LuaScript>(Component::LuaScript({scriptPath}));
}


