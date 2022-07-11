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
#include "Input.h"
#include "btBulletDynamicsCommon.h"

#define XSTR(x) STR(x)
#define STR(x) #x

using namespace DeepsEngine;
using std::filesystem::current_path;
using std::filesystem::exists;

void Application::update(bool clearScreen) {
    using clock = std::chrono::high_resolution_clock;

    auto delta_time = clock::now() - time_start;
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(delta_time).count() * 0.001;
    time_start = clock::now();
    lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

    window->processInput();

#ifndef EMSCRIPTEN
    if (firstMouse) {
        oldMousePosition = Input::GetMousePosition();
        firstMouse = false;
    } else {
        glm::vec2 dVec = Input::GetMousePosition() - oldMousePosition;
        Input::SetMouseMovement(dVec.x, dVec.y);
        oldMousePosition = Input::GetMousePosition();
    }
#endif

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

    Input::SetMouseMovement(0, 0);
}

void Application::initialize() {
    Logger::Debug("Running physics stuff");

    ///-----includes_end-----

    int i;
    ///-----initialization_start-----

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    ///-----initialization_end-----

    //keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    ///create a few basic rigid bodies

    //the ground is a cube of side 100 at position y = -56.
    //the sphere will hit it at y = -6, with center at -5
    {
        btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

        collisionShapes.push_back(groundShape);

        btTransform groundTransform;
        groundTransform.setIdentity();
        groundTransform.setOrigin(btVector3(0, -56, 0));

        btScalar mass(0.);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            groundShape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        //add the body to the dynamics world
        dynamicsWorld->addRigidBody(body);
    }

    {
        //create a dynamic rigidbody

        //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
        btCollisionShape* colShape = new btSphereShape(btScalar(1.));
        collisionShapes.push_back(colShape);

        /// Create Dynamic Objects
        btTransform startTransform;
        startTransform.setIdentity();

        btScalar mass(1.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            colShape->calculateLocalInertia(mass, localInertia);

        startTransform.setOrigin(btVector3(2, 10, 0));

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        dynamicsWorld->addRigidBody(body);
    }

    /// Do some simulation

    ///-----stepsimulation_start-----
    for (i = 0; i < 150; i++)
    {
        dynamicsWorld->stepSimulation(1.f / 60.f, 10);

        //print positions of all objects
        for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
        {
            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody* body = btRigidBody::upcast(obj);
            btTransform trans;
            if (body && body->getMotionState())
            {
                body->getMotionState()->getWorldTransform(trans);
            }
            else
            {
                trans = obj->getWorldTransform();
            }
            printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
        }
    }

    ///-----stepsimulation_end-----

    //cleanup in the reverse order of creation/initialization

    ///-----cleanup_start-----

    //remove the rigidbodies from the dynamics world and delete them
    for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    //delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++)
    {
        btCollisionShape* shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }

    //delete dynamics world
    delete dynamicsWorld;

    //delete solver
    delete solver;

    //delete broadphase
    delete overlappingPairCache;

    //delete dispatcher
    delete dispatcher;

    delete collisionConfiguration;

    //next line is optional: it will be cleared by the destructor when the array goes out of scope
    collisionShapes.clear();

    /////////

    Logger::Debug("DeepsEngine Version " + static_cast<std::string>(XSTR(DEEPS_ENGINE_VERSION)));
    Logger::Debug("Initializing engine");

    // start qt timer
#if defined(WITH_EDITOR)
    // start timer for qt to keep track of delta time
    timer.start();
    playing = false;
#else
    playing = true;
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
