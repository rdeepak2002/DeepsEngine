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
#include "PhysicsComponentSystem.h"

// Dear ImGui
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

void OpenGLRenderer::initialize() {
    Logger::Debug("Initializing renderer");

//#if defined(STANDALONE) and !defined(EMSCRIPTEN)
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        Logger::Debug("Failed to initialize GLAD");
//    } else {
//        Logger::Debug("Initialized GLAD");
//    }
//#elif defined(WITH_EDITOR)
//    // have qt initialize opengl functions
//    initializeOpenGLFunctions();
//#endif

    // screen quad VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    simpleMeshShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("simpleMeshShader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("shader.frag").c_str());

    animatedMeshShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("shader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("shader.frag").c_str());

    lightCubeShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("lightingShader.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("lightingShader.frag").c_str());

    skyboxShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("skybox.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("skybox.frag").c_str());

    physicsDebugShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("physics.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("physics.frag").c_str());

    screenShader = new Shader(
            Application::getInstance().getProjectPath().append("src").append("shaders").append("framebuffers_screen.vert").c_str(),
            Application::getInstance().getProjectPath().append("src").append("shaders").append("framebuffers_screen.frag").c_str());

    screenShader->use();
    screenShader->setInt("screenTexture", 0);

    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // load textures
    // -------------
    std::vector<std::string> faces
            {
                    Application::getInstance().getProjectPath().append("src/textures/skybox/right.png"),
                    Application::getInstance().getProjectPath().append("src/textures/skybox/left.png"),
                    Application::getInstance().getProjectPath().append("src/textures/skybox/top.png"),
                    Application::getInstance().getProjectPath().append("src/textures/skybox/bottom.png"),
                    Application::getInstance().getProjectPath().append("src/textures/skybox/front.png"),
                    Application::getInstance().getProjectPath().append("src/textures/skybox/back.png")
            };
    cubemapTexture = loadCubemap(faces);

    // shader configuration
    // --------------------
    skyboxShader->use();
    skyboxShader->setInt("skybox", 0);

    updateFrameBuffer();
}

void OpenGLRenderer::updateFrameBuffer() {
    GLint dims[4] = {0};
    glGetIntegerv(GL_VIEWPORT, dims);
    GLint fbWidth = dims[2];
    GLint fbHeight = dims[3];

    // framebuffer configuration
    // -------------------------
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fbWidth, fbHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fbWidth, fbHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLRenderer::clear() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::update() {
    // bind to framebuffer and draw scene as we normally would to color texture
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // TODO: figure out why we need this here for QT renderer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // clear screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

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

        // draw physics debug
        if (!Application::getInstance().playing) {
            physicsDebugShader->use();
            glUniformMatrix4fv(glGetUniformLocation(physicsDebugShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(physicsDebugShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
            ComponentSystem* componentSystem = Application::getInstance().componentSystems["PhysicsComponentSystem"];
            auto* physicsComponentSystem = dynamic_cast<PhysicsComponentSystem*>(componentSystem);
            physicsComponentSystem->dynamicsWorld->debugDrawWorld();
        }

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
            // update model matrix in shader
            simpleMeshShader->setMat4("model", entity.GetComponent<DeepsEngine::Component::Transform>().getModelMatrix(entity));

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
            // update model matrix in shader
            animatedMeshShader->setMat4("model", entity.GetComponent<DeepsEngine::Component::Transform>().getModelMatrix(entity));

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
        // draw skybox as last
        // projection matrix
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        view = glm::mat4(glm::mat3(view));
        projection = glm::perspective(glm::radians(mainCameraComponent.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, mainCameraComponent.zNear, mainCameraComponent.zFar);

        // draw skybox
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader->use();
        skyboxShader->setMat4("view", view);
        skyboxShader->setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
    }
    else {
        // set clear color to black to indicate no camera active
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // TODO: write text there is no camera
    }

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    screenShader->use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // render your GUI
    if(ImGui::Begin("DeepsEngine", NULL, 0))
    {
        // Using a Child allow to fill all the space of the window.
        // It also allows customization
        if(ImGui::BeginChild("GameRender"))
        {
            // Get the size of the child (i.e. the whole draw size of the windows).
//            ImVec2 wsize = ImGui::GetWindowSize();
            ImVec2 wsize = ImVec2(float(SCR_WIDTH) / 4, float(SCR_HEIGHT) / 4);
            // Because I use the texture from OpenGL, I need to invert the V from the UV.
//            ImGui::Image((ImTextureID)framebuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::Image(reinterpret_cast<ImTextureID>(textureColorbuffer), wsize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();
        }

        ImGui::End();
    }


    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
// -------------------------------------------------------
unsigned int OpenGLRenderer::loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            Logger::Error("Cubemap texture failed to load at path: " + faces[i]);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}