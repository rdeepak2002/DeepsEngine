//
// Created by Deepak Ramalingam on 2/5/22.
//

#include "Renderer.h"

#include <iostream>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <memory>
#include "src/engine/component/Component.h"

#define STB_IMAGE_IMPLEMENTATION

#include "src/engine/include/stb_image.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/Logger.h"

using std::filesystem::current_path;

#if defined(STANDALONE)
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    Renderer::getInstance().SCR_WIDTH = width;
    Renderer::getInstance().SCR_HEIGHT = height;
    // keep updating while resizing
    Renderer::getInstance().clear();
    Renderer::getInstance().update();
}
#endif

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

#if defined(STANDALONE)
void Renderer::createWindow() {
      // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Deeps Engine", NULL, NULL);
  if (window == nullptr) {
    Logger::Debug("Failed to create GLFW window");
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

bool Renderer::shouldCloseWindow() {
    if (window) {
        return glfwWindowShouldClose(window);
    } else {
        return true;
    }
}
#endif

#if defined(STANDALONE) and !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
void Renderer::closeWindow() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
//    delete ourShader;
//    ourShader = nullptr;
    glfwTerminate();
}
#endif

void Renderer::initialize() {
    Logger::Debug("initializing renderer");

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

#if !defined(STANDALONE)
    // start timer for qt to keep track of delta time
    timer.start();
#endif

#if defined(STANDALONE) and !defined(EMSCRIPTEN)
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::Debug("Failed to initialize GLAD");
    }
#elif !(defined(EMSCRIPTEN) or defined(DEVELOP_WEB))
    // have qt initialize opengl functions
    initializeOpenGLFunctions();
#endif
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

#if defined(EMSCRIPTEN)
    ourShader = new Shader(
            current_path().append("assets").append("res").append("example-project").append("shaders-web").append("shader.vert").c_str(),
            current_path().append("assets").append("res").append("example-project").append("shaders-web").append("shader.frag").c_str());
#else
    ourShader = new Shader(
            current_path().append("assets").append("res").append("example-project").append("shaders").append("shader.vert").c_str(),
            current_path().append("assets").append("res").append("example-project").append("shaders").append("shader.frag").c_str());
#endif

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    unsigned char *data = stbi_load(current_path().append("assets").append("res").append("example-project").append("textures").append("container.jpg").c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        Logger::Debug("Failed to load texture");
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load(current_path().append("assets").append("res").append("example-project").append("textures").append("awesomeface.png").c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        Logger::Debug("Failed to load texture");
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use();
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Renderer::update() {
#if defined(INCLUDE_DEEPS_ENGINE_LIBRARY)
    glEnable(GL_DEPTH_TEST);
#endif

    // per-frame time logic
    // --------------------
    float currentFrame;

#if defined(INCLUDE_DEEPS_ENGINE_LIBRARY)
    currentFrame = static_cast<float>(timer.elapsed()) / 1000.0f;
#else
    currentFrame = static_cast<float>(glfwGetTime());
#endif

    // calculate delta time
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // activate shader
    ourShader->use();

    std::vector<DeepsEngine::Entity> cameraEntities = scene.GetCameraEntities();

    if (cameraEntities.size() > 0) {
        // get main camera
        std::unique_ptr<DeepsEngine::Entity> mainCameraEntity = std::make_unique<DeepsEngine::Entity>(cameraEntities.front());
        DeepsEngine::Component::Camera mainCameraComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Camera>();
        DeepsEngine::Component::Transform mainCameraTransformComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Transform>();

        // set the clear color to light blue ish
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // create transformations
        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(mainCameraComponent.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, mainCameraComponent.zNear, mainCameraComponent.zFar);
        cameraPos.x = mainCameraTransformComponent.position.x;
        cameraPos.y = mainCameraTransformComponent.position.y;
        cameraPos.z = mainCameraTransformComponent.position.z;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // pass transformation matrices to the shader
        ourShader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader->setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);

        // get current scene and all the entities
        for(auto entity : scene.GetDrawableEntities()) {
            // get the entity's transform
            auto entityTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
            auto entityPosition = entityTransform.position;
            auto entityRotation = entityTransform.rotation;
            auto entityScale = entityTransform.scale;

            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

            // translate the model
            model = glm::translate(model, glm::vec3(entityPosition.x, entityPosition.y, entityPosition.z));

            // rotate the model
            // rotate x
            model = glm::rotate(model, entityRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

            // rotate y
            model = glm::rotate(model, entityRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

            // rotate z
            model = glm::rotate(model, entityRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

            // Scale the model
            model = glm::scale(model, glm::vec3(entityScale.x, entityScale.y, entityScale.z));

            ourShader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    else {
        // set clear color to black to indicate no camera active
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

#if defined(STANDALONE)
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
#endif

    // TODO: create separate (singleton?) class called Application which handles this stuff (and maybe physics) in the future
    for(auto entity : Renderer::getInstance().scene.GetScriptableEntities()) {
        DeepsEngine::Component::LuaScript luaScriptComponent = entity.GetComponent<DeepsEngine::Component::LuaScript>();
        // sol::environment my_other_env(lua, sol::create, lua.globals());
        lua.script_file(luaScriptComponent.scriptPath);

        sol::function onCreateFunc = lua["onCreate"];

//        if (!entity.scriptOnCreateInvoked) {
//            entity.scriptOnCreateInvoked = true;
//
//            if (onCreateFunc) {
//                onCreateFunc(entity);
//            } else {
//                Logger::Warn("No on create function in script");
//            }
//        }

        sol::function onUpdateFunc = lua["onUpdate"];

        if (onUpdateFunc) {
            onUpdateFunc(entity, deltaTime);
        } else {
            Logger::Warn("No on update function in script");
        }
    }

    return deltaTime;
}

#if defined(STANDALONE) and !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
void Renderer::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
#endif
