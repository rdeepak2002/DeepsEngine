//
// Created by Deepak Ramalingam on 4/30/22.
//
#include "Application.h"
#include "Renderer.h"
#include "Entity.h"
#include "Component.h"
#include <iostream>
#include <glm/ext.hpp>

#define XSTR(x) STR(x)
#define STR(x) #x

using namespace DeepsEngine;
using std::filesystem::current_path;
using std::filesystem::exists;

void Application::update(bool clearScreen) {
    // calculate delta time
    float currentFrame = renderer->getCurrentTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // update renderer
    renderer->processInput();

    if (clearScreen) {
        renderer->clear();
    }

    renderer->update();

    // update lua component systems
    for (auto& componentSystem : componentSystems) {
        componentSystem->update(deltaTime);
    }
}

void Application::initialize() {
    Logger::Debug("DeepsEngine Version " + static_cast<std::string>(XSTR(DEEPS_ENGINE_VERSION)));

    Application::getInstance().createSampleEntities();

    // create window
    renderer->createWindow();

    // initialize renderer
    renderer->initialize();

    // initialize component systems
    for (auto& componentSystem : componentSystems) {
        componentSystem->init();
    }
}

void Application::close() {
    renderer->closeWindow();
}

bool Application::shouldClose() {
    return renderer->shouldCloseWindow();
}

void Application::createSampleEntities() {
    // add camera entity
    Entity camera = Application::getInstance().scene.CreateEntity("Scene Camera");
    (&camera.GetComponent<Component::Transform>())->position.z = 5.0;
    (&camera.GetComponent<Component::Transform>())->rotation.x = 0.0;
    (&camera.GetComponent<Component::Transform>())->rotation.y = -glm::half_pi<float>();
    (&camera.GetComponent<Component::Transform>())->rotation.z = 0.0;
    camera.AddComponent<Component::Camera>(Component::Camera({45.0f, 0.1f, 100.0f}));
    std::string cameraScriptPath = getProjectPath().append("scripts").append("scene-camera.lua");
    camera.AddComponent<Component::LuaScript>(Component::LuaScript({cameraScriptPath}));

    // add a single cube entity
    Entity entity = Application::getInstance().scene.CreateEntity("Cube");
    (&entity.GetComponent<Component::Transform>())->position.y = -1.2;
    entity.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube"});
    std::string scriptPath = getProjectPath().append("scripts").append("script.lua");
    entity.AddComponent<Component::LuaScript>(Component::LuaScript({scriptPath}));

    // add a single cube entity
    Entity entity2 = Application::getInstance().scene.CreateEntity("Cube 2");
    (&entity2.GetComponent<Component::Transform>())->position.x = -1.0;
    entity2.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube"});
}

void Application::clearRenderer() {
    renderer->clear();
}

void Application::resizeWindow(unsigned int width, unsigned int height, bool update) {
    renderer->SCR_WIDTH = width;
    renderer->SCR_HEIGHT = height;

    if (update) {
        renderer->clear();
        renderer->update();
    }
}

std::filesystem::path Application::getProjectPath() {
    if (projectPath.empty()) {
        Logger::Warn("Falling back to development project path");
        projectPath = std::filesystem::current_path().append("assets").append("res").append("example-project");
    }

    return std::filesystem::path(projectPath);
}

void Application::setProjectPath(std::string projectPath) {
    this->projectPath = projectPath;
}


