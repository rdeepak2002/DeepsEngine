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
    Renderer::getInstance().processInput();

    if (clearScreen) {
        Renderer::getInstance().clear();
    }

    Renderer::getInstance().update();
}

void Application::createWindow() {
    Renderer::getInstance().createWindow();
}

void Application::initialize() {
    Renderer::getInstance().initialize();
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


