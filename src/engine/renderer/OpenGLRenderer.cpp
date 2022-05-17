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

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float cubeVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

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

    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // set unsigned texture
    std::string missingTextureDiffuseFilePath = Application::getInstance().getProjectPath().append("src").append("textures").append("missing_texture.png");
    std::string missingTextureSpecularFilePath = Application::getInstance().getProjectPath().append("src").append("textures").append("missing_texture_specular.png");
    missingTextureDiffuse = loadTexture(missingTextureDiffuseFilePath.c_str());
    missingTextureSpecular = loadTexture(missingTextureSpecularFilePath.c_str());

    std::string linkIdleModelPath = Application::getInstance().getProjectPath().append("src").append("models").append("link").append("animations").append("idle").append("Idle.dae");
    std::string linkIdleModelPathFbx = Application::getInstance().getProjectPath().append("src").append("models").append("link_fbx").append("Idle.fbx");
    std::string linkDancingModelPathFbx = Application::getInstance().getProjectPath().append("src").append("models").append("link_fbx").append("Dancing.fbx");
    std::string backpackModelPath = Application::getInstance().getProjectPath().append("src").append("models").append("backpack").append("backpack.obj");

    bool flipTextures = true;

    stbi_set_flip_vertically_on_load(flipTextures);

//    backpackModel = new Model(backpackModelPath);

    ourModel = new AnimatedModel(linkIdleModelPathFbx);

    stbi_set_flip_vertically_on_load(false);

    Animation* dancingAnimation = new Animation(linkDancingModelPathFbx, ourModel);
    animator = new Animator(dancingAnimation);
}

void OpenGLRenderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::update() {
    // TODO: figure out why we need this here for QT renderer
    glEnable(GL_DEPTH_TEST);

//    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    animator->UpdateAnimation(Application::getInstance().deltaTime);

    std::vector<DeepsEngine::Entity> cameraEntities = Application::getInstance().scene.GetCameraEntities();

    if (!cameraEntities.empty()) {
        // get main camera entity and its components
        std::unique_ptr<DeepsEngine::Entity> mainCameraEntity = std::make_unique<DeepsEngine::Entity>(cameraEntities.front());
        DeepsEngine::Component::Camera mainCameraComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Camera>();
        DeepsEngine::Component::Transform mainCameraTransformComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Transform>();

        // get camera vectors
        glm::vec3 cameraFront = mainCameraTransformComponent.front();
        glm::vec3 cameraUp = mainCameraTransformComponent.up();
        glm::vec3 cameraPos = mainCameraTransformComponent.position;

        // calculate projection matrix
        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(mainCameraComponent.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, mainCameraComponent.zNear, mainCameraComponent.zFar);

        // calculate view matrix
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // be sure to activate shader when setting uniforms/drawing objects
        simpleMeshShader->use();
        simpleMeshShader->setVec3("viewPos", cameraPos);
        applyLighting(simpleMeshShader);
        simpleMeshShader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        simpleMeshShader->setMat4("view", view);

        // get all entities with meshes
        for(auto entity : Application::getInstance().scene.GetDrawableEntities()) {
            // get the entity's transform
            auto entityTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
            auto entityPosition = entityTransform.position;
            auto entityRotation = entityTransform.rotation;
            auto entityScale = entityTransform.scale;

            // get diffuse and specular map from entity material
            unsigned int diffuseMap = missingTextureDiffuse;
            unsigned int specularMap = missingTextureSpecular;
            float materialShininess = 32.0f;

            if (entity.HasComponent<DeepsEngine::Component::Material>()) {
                diffuseMap = entity.GetComponent<DeepsEngine::Component::Material>().diffuse;
                specularMap = entity.GetComponent<DeepsEngine::Component::Material>().specular;
                materialShininess = entity.GetComponent<DeepsEngine::Component::Material>().shininess;
            }

            // bind diffuse map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);

            // bind specular map
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap);

            // bind texture maps
            simpleMeshShader->setInt("material.diffuse", 0);
            simpleMeshShader->setInt("material.specular", 1);
            simpleMeshShader->setFloat("material.shininess", materialShininess);

            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

            // translate the model
            model = glm::translate(model, glm::vec3(entityPosition.x, entityPosition.y, entityPosition.z));

            // rotate x
            model = glm::rotate(model, entityRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

            // rotate y
            model = glm::rotate(model, entityRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

            // rotate z
            model = glm::rotate(model, entityRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

            // Scale the model
            model = glm::scale(model, glm::vec3(entityScale.x, entityScale.y, entityScale.z));

            simpleMeshShader->setMat4("model", model);

            // render the cube
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

//        glm::mat4 backpackLoc = glm::mat4(1.0f);
//        backpackLoc = glm::translate(backpackLoc, glm::vec3(0.0f, 0.0f, 0.0f));
//        backpackLoc = glm::scale(backpackLoc, glm::vec3(1.0f, 1.0f, 1.0f));
//        simpleMeshShader->setMat4("model", backpackLoc);
//        backpackModel->Draw(*simpleMeshShader);

        animatedMeshShader->use();
        animatedMeshShader->setVec3("viewPos", cameraPos);
        applyLighting(animatedMeshShader);
        animatedMeshShader->setMat4("projection", projection);
        animatedMeshShader->setMat4("view", view);
        animatedMeshShader->setFloat("material.shininess", 256.0f);

        auto transforms = animator->GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
            animatedMeshShader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        animatedMeshShader->setMat4("model", model);

        ourModel->Draw(*animatedMeshShader);

        // also draw the lamp object(s)
        lightCubeShader->use();
        lightCubeShader->setMat4("projection", projection);
        lightCubeShader->setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        // don't render directional light due to how it behaves
        // TODO: draw gizmo for directional light
//        for (DeepsEngine::Entity entity : directionalLights) {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, entity.GetComponent<DeepsEngine::Component::Transform>().position);
//            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
//            lightCubeShader->setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
        // TODO: draw gizmo for point light
        auto lightEntities = Application::getInstance().scene.GetLightEntities();

        std::vector<DeepsEngine::Entity> pointLights = std::get<1>(lightEntities);

        for (DeepsEngine::Entity entity : pointLights) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, entity.GetComponent<DeepsEngine::Component::Transform>().position);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightCubeShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // TODO: draw gizmo for spot light
//        for (DeepsEngine::Entity entity : spotLights) {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, entity.GetComponent<DeepsEngine::Component::Transform>().position);
//            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
//            lightCubeShader->setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
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
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
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
