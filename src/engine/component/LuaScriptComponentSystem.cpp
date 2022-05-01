//
// Created by Deepak Ramalingam on 5/1/22.
//

#include "LuaScriptComponentSystem.h"
#include "src/engine/Application.h"
#include "src/engine/scene/Entity.h"
#include "Component.h"
#include <iostream>

void LuaScriptComponentSystem::init() {
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

void LuaScriptComponentSystem::update(float deltaTime) {
    for(auto entity : Application::getInstance().scene.GetScriptableEntities()) {
        auto &luaScriptComponent = entity.GetComponent<DeepsEngine::Component::LuaScript>();
        lua.script_file(luaScriptComponent.scriptPath);

        if (entity.IsValid() && luaScriptComponent.shouldInit) {
            luaScriptComponent.self = lua.create_table_with("value", "key");
            lua["self"] = luaScriptComponent.self;

            auto f = lua["init"];

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
