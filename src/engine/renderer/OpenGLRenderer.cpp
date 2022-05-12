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

glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
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

    std::string shaderFolderName = "shaders";

    ourShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append(shaderFolderName).append("shader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append(shaderFolderName).append("shader.frag").c_str());

    lightingShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append(shaderFolderName).append("lightingShader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append(shaderFolderName).append("lightingShader.frag").c_str());

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

    diffuseMap = loadTexture(Application::getInstance().getProjectPath().append("src").append("textures").append("container2.png").c_str());
    specularMap = loadTexture(Application::getInstance().getProjectPath().append("src").append("textures").append("container2_specular.png").c_str());

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use();
    ourShader->setInt("material.diffuse", 0);
    ourShader->setInt("material.specular", 1);
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

    // be sure to activate shader when setting uniforms/drawing objects
    ourShader->use();
    ourShader->setVec3("viewPos", cameraPos);
    ourShader->setFloat("material.shininess", 32.0f);

    // define current number of point lights
    ourShader->setInt("numberOfDirLights", 1);
    ourShader->setInt("numberOfPointLights", 4);
    ourShader->setInt("numberOfSpotLights", 1);

    // directional light
    ourShader->setVec3("dirLights[0].direction", -0.2f, -1.0f, -0.3f);
    ourShader->setVec3("dirLights[0].ambient", 0.05f, 0.05f, 0.05f);
    ourShader->setVec3("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f);
    ourShader->setVec3("dirLights[0].specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    ourShader->setVec3("pointLights[0].position", pointLightPositions[0]);
    ourShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    ourShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    ourShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    ourShader->setFloat("pointLights[0].constant", 1.0f);
    ourShader->setFloat("pointLights[0].linear", 0.09f);
    ourShader->setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    ourShader->setVec3("pointLights[1].position", pointLightPositions[1]);
    ourShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    ourShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    ourShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    ourShader->setFloat("pointLights[1].constant", 1.0f);
    ourShader->setFloat("pointLights[1].linear", 0.09f);
    ourShader->setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    ourShader->setVec3("pointLights[2].position", pointLightPositions[2]);
    ourShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    ourShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    ourShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    ourShader->setFloat("pointLights[2].constant", 1.0f);
    ourShader->setFloat("pointLights[2].linear", 0.09f);
    ourShader->setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    ourShader->setVec3("pointLights[3].position", pointLightPositions[3]);
    ourShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    ourShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    ourShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    ourShader->setFloat("pointLights[3].constant", 1.0f);
    ourShader->setFloat("pointLights[3].linear", 0.09f);
    ourShader->setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight
    ourShader->setVec3("spotLights[0].position", cameraPos);
    ourShader->setVec3("spotLights[0].direction", cameraFront);
    ourShader->setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
    ourShader->setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
    ourShader->setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
    ourShader->setFloat("spotLights[0].constant", 1.0f);
    ourShader->setFloat("spotLights[0].linear", 0.09f);
    ourShader->setFloat("spotLights[0].quadratic", 0.032f);
    ourShader->setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
    ourShader->setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));

    std::vector<DeepsEngine::Entity> cameraEntities = Application::getInstance().scene.GetCameraEntities();

    if (cameraEntities.size() > 0) {
        // get main camera
        std::unique_ptr<DeepsEngine::Entity> mainCameraEntity = std::make_unique<DeepsEngine::Entity>(cameraEntities.front());
        DeepsEngine::Component::Camera mainCameraComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Camera>();
        DeepsEngine::Component::Transform mainCameraTransformComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Transform>();

        // get camera facing direction
        cameraFront = mainCameraTransformComponent.front();

        // create transformations
        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(mainCameraComponent.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, mainCameraComponent.zNear, mainCameraComponent.zFar);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
        cameraPos.x = mainCameraTransformComponent.position.x;
        cameraPos.y = mainCameraTransformComponent.position.y;
        cameraPos.z = mainCameraTransformComponent.position.z;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // pass transformation matrices to the shader
        ourShader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader->setMat4("view", view);

        // get all entities with meshes
        for(auto entity : Application::getInstance().scene.GetDrawableEntities()) {
            // get the entity's transform
            auto entityTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
            auto entityPosition = entityTransform.position;
            auto entityRotation = entityTransform.rotation;
            auto entityScale = entityTransform.scale;

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

            ourShader->setMat4("model", model);

            // bind diffuse map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);
            // bind specular map
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap);

            // render the cube
            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // also draw the lamp object(s)
        lightingShader->use();
        lightingShader->setMat4("projection", projection);
        lightingShader->setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightingShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    else {
        // set clear color to black to indicate no camera active
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // TODO: write text there is no camera
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
