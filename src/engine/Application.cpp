//
// Created by Deepak Ramalingam on 4/30/22.
//
#include "Application.h"
#include "OpenGLRenderer.h"
#include "Entity.h"
#include "Component.h"
#include <iostream>
#include <glm/ext.hpp>
#include <yaml-cpp/yaml.h>

#define XSTR(x) STR(x)
#define STR(x) #x

using namespace DeepsEngine;
using std::filesystem::current_path;
using std::filesystem::exists;

void Application::update(bool clearScreen) {
    using clock = std::chrono::high_resolution_clock;

    auto delta_time = clock::now() - time_start;
    time_start = clock::now();
    lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

    window->processInput();

    // update game logic as lag permits
    while(lag >= timestep) {
        lag -= timestep;

        for (auto& componentSystem : componentSystems) {
            componentSystem->update(std::chrono::duration_cast<std::chrono::milliseconds>(timestep).count() * 0.001);
        }
    }

    // used for interpolated state
    float alpha = (float) lag.count() / timestep.count();

    // calculate how close or far we are from the next timestep
    if (clearScreen) {
        renderer->clear();
    }
    renderer->update();
    window->swapBuffers();
    window->pollEvents();
}

void Application::initialize() {
    Logger::Debug("DeepsEngine Version " + static_cast<std::string>(XSTR(DEEPS_ENGINE_VERSION)));
    Logger::Debug("Initializing engine");

    // start qt timer
#if defined(WITH_EDITOR)
    // start timer for qt to keep track of delta time
    timer.start();
#endif

    // add component systems
    componentSystems.clear();
    componentSystems.push_back(std::make_unique<LuaScriptComponentSystem>());
    componentSystems.push_back(std::make_unique<NativeScriptComponentSystem>());

    // create window
    window->createWindow();

    // initialize renderer
    renderer->initialize();

    // load the project and deserialize all entities
    loadProject();

    // initialize component systems
    for (auto& componentSystem : componentSystems) {
        componentSystem->init();
    }

    using clock = std::chrono::high_resolution_clock;
    lag = 0ns;
    time_start = clock::now();
}

void Application::close() {
    Logger::Debug("Destroying engine");
    for (auto& componentSystem : componentSystems) {
        componentSystem->destroy();
    }

    renderer->deinit();
    window->closeWindow();
}

bool Application::shouldClose() {
    return window->shouldCloseWindow();
}

void Application::createSampleEntities() {
    Logger::Debug("Creating sample entities");

    // add camera entity
    Entity camera = Application::getInstance().scene.CreateEntity("Scene Camera");
    (&camera.GetComponent<Component::Transform>())->position.z = 5.0;
    (&camera.GetComponent<Component::Transform>())->rotation.x = 0.0;
    (&camera.GetComponent<Component::Transform>())->rotation.y = -glm::half_pi<float>();
    (&camera.GetComponent<Component::Transform>())->rotation.z = 0.0;
    camera.AddComponent<Component::Camera>(Component::Camera({45.0f, 0.1f, 100.0f}));
    std::string simpleScript = std::filesystem::path("src").append("scripts").append("scene-camera.lua");
    camera.AddComponent<Component::LuaScript>(Component::LuaScript({simpleScript}));

    // add a single cube entity
    Entity entity = Application::getInstance().scene.CreateEntity("Cube");
    (&entity.GetComponent<Component::Transform>())->position.y = -1.2;
    entity.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube", entity.GetComponent<Component::Id>().id});
    std::string cameraScript = std::filesystem::path("src").append("scripts").append("script.lua");
    entity.AddComponent<Component::LuaScript>(Component::LuaScript({cameraScript}));

    // add a single cube entity
    Entity entity2 = Application::getInstance().scene.CreateEntity("Cube 2");
    (&entity2.GetComponent<Component::Transform>())->position.x = -1.0;
    entity2.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube", entity.GetComponent<Component::Id>().id});
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
        window->swapBuffers();
        window->pollEvents();
    }
}

std::filesystem::path Application::getProjectPath() {
#ifdef EMSCRIPTEN
    if (projectPath.empty()) {
        projectPath = std::filesystem::current_path().append("assets").append("project");
    }
#else
    if (projectPath.empty()) {
        Logger::Debug("Using default project path");
        projectPath = std::filesystem::current_path().append("assets").append("res").append("example-project");
//        Application::getInstance().createSampleEntities();
    }
#endif

    return std::filesystem::path(projectPath);
}

void Application::setProjectPath(std::string projectPath) {
    this->projectPath = projectPath;

    // load the project (deserialize the entities)
//    loadProject();
}

void Application::loadProject() {
    scene.DestroyAllEntities();

    std::string loadScenePath = std::filesystem::path(Application::getProjectPath()).append("src").append("main.scene");

    YAML::Node doc = YAML::LoadFile(loadScenePath);
    std::string sceneName = doc["Scene"].as<std::string>();
    std::vector<YAML::Node> entitiesYaml = doc["Entities"].as<std::vector<YAML::Node>>();

    for (YAML::Node entityYaml : entitiesYaml) {
        Entity entity = scene.CreateEntity();
        entity.Deserialize(entityYaml);
    }
}

void Application::saveProject() {
    std::string savePath = std::filesystem::path(Application::getProjectPath()).append("src").append("main.scene");

    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "Scene" << YAML::Value << "example-scene";

    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

    scene.registry.each([&](auto entityId) {
        Entity entity = { entityId };

        if (!entity) {
            return;
        }

        entity.Serialize(out);
    });

    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fout(savePath);
    fout << out.c_str();
}

std::pair<unsigned int, unsigned int> Application::getWindowDimensions() {
    return {renderer->SCR_WIDTH, renderer->SCR_HEIGHT};
}

float Application::getCurrentTime() {
#if defined(WITH_EDITOR)
    return static_cast<float>(timer.elapsed()) / 1000.0f;
#else
    return static_cast<float>(glfwGetTime());
#endif
}

