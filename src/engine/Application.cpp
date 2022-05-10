//
// Created by Deepak Ramalingam on 4/30/22.
//
#include "Application.h"
#include "Renderer.h"
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
    entity.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube"});
    std::string cameraScript = std::filesystem::path("src").append("scripts").append("script.lua");
    entity.AddComponent<Component::LuaScript>(Component::LuaScript({cameraScript}));

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
#ifdef EMSCRIPTEN
    if (projectPath.empty()) {
        projectPath = std::filesystem::current_path().append("assets").append("project");
    }
#else
    if (projectPath.empty()) {
        Logger::Warn("Falling back to development project path");
        projectPath = std::filesystem::current_path().append("assets").append("res").append("example-project");
        Application::getInstance().createSampleEntities();
    }
#endif

    return std::filesystem::path(projectPath);
}

void Application::setProjectPath(std::string projectPath) {
    this->projectPath = projectPath;

    // load the project (deserialize the entities)
    loadProject();
}

void Application::loadProject() {
    std::string loadScenePath = std::filesystem::path(Application::getProjectPath()).append("src").append("example.scene");


//
//    Yaml::Node root;
//
//    try
//    {
//        Parse(root, loadScenePath.c_str());
//        Logger::Debug("Loaded scene file: " + loadScenePath);
//    }
//    catch (const Yaml::Exception e)
//    {
//        Logger::Error("Error reading scene file: " + loadScenePath);
//        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
//        return;
//    }
//
//    Logger::Debug("Loaded scene: " + root["Scene"].As<std::string>());
}

void Application::saveProject() {
    std::string savePath = std::filesystem::path(Application::getProjectPath()).append("src").append("example.scene");

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

//    Yaml::Node root;
//
//    // define what to serialize in object
//    root["Scene"] = "example-project-scene-1";
//
//    // TODO: serialize list of entities
//    // TODO: this is the wrong syntax! fix it
////    Yaml::Node entity;
////    entity["Id"] = "sample-entity-id";
//
//    std::string blankYamlArr = "list:"
//                               "  - hello world";
//
//    Yaml::Node entityArray;
//
//    try {
//        Yaml::Parse(entityArray, blankYamlArr);
//    }
//    catch (const Yaml::Exception e)
//    {
//        Logger::Error("Error parsing blank yaml array");
//        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
//        std::cin.get();
//    }
//
////    entityArray["Entities"][0] = "Entity1";
//
////    Yaml::
//
////    std::string entitiesArrData = "";
////    std::string entitiesArrData =
////            "\t- Entity1: entityId\n"
////            "\t\tTag: tagComponentData\n"
////            "\t- Entity2: entity2Id\n"
////            "\t\tTag: tagComponentData\n";
//
////    auto entityHandles = scene.registry.view<DeepsEngine::Component::Tag>();
////
////    for (auto entityHandle : entityHandles) {
////        DeepsEngine::Entity entity = {entityHandle};
////
////        entitiesArrData.append("\t- Entity: ").append(std::to_string(entity.GetId())).append("\n");
////    }
//
////    Yaml::Node entitiesArrNode;
//
////    try
////    {
////        Parse(entitiesArrNode, entitiesArrData);
////    }
////    catch (const Yaml::Exception e)
////    {
////        Logger::Error("Error parsing entities array data");
////        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
////        return;
////    }
//
//    root["list"] = entityArray;
//
////    Yaml::Iterator
////    root["Entities"] = entity;
////    std::vector<std::string> testArr;
////    testArr.push_back("exampleVal");
////    root["Entities"] = testArr;
////    root["Entities"][0] = entity;
//
//    std::string savePath = std::filesystem::path(Application::getProjectPath()).append("example.scene");
//
//    try
//    {
//        Serialize(root, savePath.c_str());
//        Logger::Debug("Successfully saved scene to: " + savePath);
//    }
//    catch (const Yaml::Exception e)
//    {
//        Logger::Error("Error saving scene to: " + savePath);
//        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
//        std::cin.get();
//    }
//
//    // refresh project to be safe
////    loadProject();
}


