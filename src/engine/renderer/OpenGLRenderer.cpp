//
// Created by Deepak Ramalingam on 2/5/22.
//

#include "OpenGLRenderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <memory>
#include "Component.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Entity.h"
#include "Logger.h"
#include "Application.h"
#include "Input.h"
#include "glm/gtx/compatibility.hpp"

void OpenGLRenderer::initialize() {
    Logger::Debug("Initializing renderer");

#if defined(STANDALONE) and !defined(EMSCRIPTEN)
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::Debug("Failed to initialize GLAD");
    }
#elif defined(WITH_EDITOR)
    // have qt initialize opengl functions
    initializeOpenGLFunctions();
#endif

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    simpleMeshShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("simpleMeshShader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("shader.frag").c_str());

    animatedMeshShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("shader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("shader.frag").c_str());

    lightCubeShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("lightingShader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("lightingShader.frag").c_str());
}

void OpenGLRenderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::update() {
    // TODO: figure out why we need this here for QT renderer
    glEnable(GL_DEPTH_TEST);

    // clear screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update model animation
//    animator->UpdateAnimation(Application::getInstance().deltaTime);

    // get all cameras in scene
    std::vector<DeepsEngine::Entity> cameraEntities = Application::getInstance().scene.GetCameraEntities();

    if (!cameraEntities.empty()) {
        // get main camera
        std::unique_ptr<DeepsEngine::Entity> mainCameraEntity = std::make_unique<DeepsEngine::Entity>(cameraEntities.front());
        DeepsEngine::Component::Camera mainCameraComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Camera>();
        DeepsEngine::Component::Transform mainCameraTransformComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Transform>();

        // main camera vectors
        glm::vec3 cameraFront = mainCameraTransformComponent.front();
        glm::vec3 cameraUp = mainCameraTransformComponent.up();
        glm::vec3 cameraPos = mainCameraTransformComponent.position;

        // projection matrix
        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(mainCameraComponent.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, mainCameraComponent.zNear, mainCameraComponent.zFar);

        // view matrix
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // get all entities with meshes
        auto meshEntities = Application::getInstance().scene.GetMeshEntities();
        auto staticMeshEntities = std::get<0>(meshEntities);
        auto animatedMeshEntities = std::get<1>(meshEntities);

        // activate shader to draw simple meshes without animations
        simpleMeshShader->use();
        simpleMeshShader->setVec3("viewPos", cameraPos);
        applyLighting(simpleMeshShader);
        simpleMeshShader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        simpleMeshShader->setMat4("view", view);

        for(auto entity : staticMeshEntities) {
            // get the entity's transform
            auto entityTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
            auto entityPosition = entityTransform.position;
            auto entityRotation = entityTransform.rotation;
            auto entityScale = entityTransform.scale;

            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, glm::vec3(entityPosition.x, entityPosition.y, entityPosition.z));
            model = glm::rotate(model, entityRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, entityRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, entityRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(entityScale.x, entityScale.y, entityScale.z));

            // update model matrix in shader
            simpleMeshShader->setMat4("model", model);

            // render the mesh
            entity.GetComponent<DeepsEngine::Component::MeshFilter>().draw(entity, simpleMeshShader);
        }

        // activate shader to draw meshes with animation
        animatedMeshShader->use();
        animatedMeshShader->setVec3("viewPos", cameraPos);
        applyLighting(animatedMeshShader);
        animatedMeshShader->setMat4("projection", projection);
        animatedMeshShader->setMat4("view", view);

        for (auto entity : animatedMeshEntities) {
            // get the entity's transform
            auto entityTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
            auto entityPosition = entityTransform.position;
            auto entityRotation = entityTransform.rotation;
            auto entityScale = entityTransform.scale;

            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, glm::vec3(entityPosition.x, entityPosition.y, entityPosition.z));
            model = glm::rotate(model, entityRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, entityRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, entityRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(entityScale.x, entityScale.y, entityScale.z));

            // update model matrix in shader
            animatedMeshShader->setMat4("model", model);

            // render the mesh
            entity.GetComponent<DeepsEngine::Component::MeshFilter>().draw(entity, animatedMeshShader);
        }

        // draw lights, TODO: draw them as 2D gizmos
        lightCubeShader->use();
        lightCubeShader->setMat4("projection", projection);
        lightCubeShader->setMat4("view", view);
        auto lightEntities = Application::getInstance().scene.GetLightEntities();
        std::vector<DeepsEngine::Entity> pointLights = std::get<1>(lightEntities);
        for (DeepsEngine::Entity entity : pointLights) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, entity.GetComponent<DeepsEngine::Component::Transform>().position);
            model = glm::scale(model, glm::vec3(0.2f)); // smaller cube
            lightCubeShader->setMat4("model", model);
            entity.GetComponent<DeepsEngine::Component::Light>().draw();
        }
    }
    else {
        // set clear color to black to indicate no camera active
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // TODO: write text there is no camera
    }
}

void OpenGLRenderer::applyLighting(Shader* shader) {
    auto lightEntities = Application::getInstance().scene.GetLightEntities();
    std::vector<DeepsEngine::Entity> directionalLights = std::get<0>(lightEntities);
    std::vector<DeepsEngine::Entity> pointLights = std::get<1>(lightEntities);
    std::vector<DeepsEngine::Entity> spotLights = std::get<2>(lightEntities);

    // define current number of point lights
    shader->setInt("numberOfDirLights", directionalLights.size());
    shader->setInt("numberOfPointLights", pointLights.size());
    shader->setInt("numberOfSpotLights", spotLights.size());

    for (int i = 0; i < directionalLights.size(); i++) {
        DeepsEngine::Entity lightEntity = directionalLights.at(i);
        DeepsEngine::Component::Light lightComponent = lightEntity.GetComponent<DeepsEngine::Component::Light>();
        std::string prefix = "dirLights[" + std::to_string(i) + "]";
        shader->setVec3(prefix + ".direction", lightEntity.GetComponent<DeepsEngine::Component::Transform>().rotation);   // TODO: instead of direction, use entity rotation
        shader->setVec3(prefix + ".ambient", lightComponent.ambient);
        shader->setVec3(prefix + ".diffuse", lightComponent.diffuse);
        shader->setVec3(prefix + ".specular", lightComponent.specular);
    }

    for (int i = 0; i < pointLights.size(); i++) {
        DeepsEngine::Entity lightEntity = pointLights.at(i);
        DeepsEngine::Component::Light lightComponent = lightEntity.GetComponent<DeepsEngine::Component::Light>();
        std::string prefix = "pointLights[" + std::to_string(i) + "]";
        shader->setVec3(prefix + ".position", lightEntity.GetComponent<DeepsEngine::Component::Transform>().position);
        shader->setVec3(prefix + ".ambient", lightComponent.ambient);
        shader->setVec3(prefix + ".diffuse", lightComponent.diffuse);
        shader->setVec3(prefix + ".specular", lightComponent.specular);
        shader->setFloat(prefix + ".constant", lightComponent.constant);
        shader->setFloat(prefix + ".linear", lightComponent.linear);
        shader->setFloat(prefix + ".quadratic", lightComponent.quadratic);
    }

    for (int i = 0; i < spotLights.size(); i++) {
        DeepsEngine::Entity lightEntity = spotLights.at(i);
        DeepsEngine::Component::Light lightComponent = lightEntity.GetComponent<DeepsEngine::Component::Light>();
        std::string prefix = "spotLights[" + std::to_string(i) + "]";
        shader->setVec3(prefix + ".position", lightEntity.GetComponent<DeepsEngine::Component::Transform>().position);
        shader->setVec3(prefix + ".direction", lightEntity.GetComponent<DeepsEngine::Component::Transform>().front());  // TODO: consider changing this to .rotation
        shader->setVec3(prefix + ".ambient", lightComponent.ambient);
        shader->setVec3(prefix + ".diffuse", lightComponent.diffuse);
        shader->setVec3(prefix + ".specular", lightComponent.specular);
        shader->setFloat(prefix + ".constant", lightComponent.constant);
        shader->setFloat(prefix + ".linear", lightComponent.linear);
        shader->setFloat(prefix + ".quadratic", lightComponent.quadratic);
        shader->setFloat(prefix + ".cutOff", glm::cos(glm::radians(lightComponent.cutOff)));
        shader->setFloat(prefix + ".outerCutOff", glm::cos(glm::radians(lightComponent.outerCutOff)));
    }
}

void OpenGLRenderer::deinit() {
#if defined(STANDALONE) and !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
#endif
}

unsigned int OpenGLRenderer::loadTexture(char const * path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        Logger::Error("Texture failed to load at path: " + std::string(path));
        stbi_image_free(data);
    }

    return textureID;
}
