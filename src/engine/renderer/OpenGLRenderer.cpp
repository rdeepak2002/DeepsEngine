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
#include <imgui_internal.h>

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

    ImGui_ImplOpenGL3_Init("#version 330");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

#if !defined(EMSCRIPTEN)
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::Debug("Failed to initialize GLAD");
    } else {
        Logger::Debug("Initialized GLAD");
    }
#endif

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set clear color to black (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

#ifdef STANDALONE
    screenShader->use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
#endif

#ifdef WITH_EDITOR
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ///

    ImGuiStyle * style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 4.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
//    style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
//    style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
//    style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
//    style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
//    style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
//    style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
//    style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
//    style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    ///

    if (defaultFont) {
        ImGui::PushFont(defaultFont);
    }

    ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
    ImGuiID dockspaceID = ImGui::GetID("DeepsEngine");

    if (!ImGui::DockBuilderGetNode(dockspaceID)) {
        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);
//        ImGui::DockBuilderSetNodePos(dockspaceID, ImVec2(0.0f, 0.0f));
//        ImGui::DockBuilderSetNodeSize(dockspaceID, ImGui::GetIO().DisplaySize);

        ImGuiID dock_main_id = dockspaceID;
        ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_up_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.05f, nullptr, &dock_main_id);
        ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);

        ImGui::DockBuilderDockWindow("Renderer", dock_main_id);
        ImGui::DockBuilderDockWindow("Scene", dock_left_id);
        ImGui::DockBuilderDockWindow("Inspector", dock_right_id);
        ImGui::DockBuilderDockWindow("Actions", dock_up_id);
        ImGui::DockBuilderDockWindow("Console", dock_down_id);

        // Disable tab bar for custom toolbar
        ImGuiDockNode* node = ImGui::DockBuilderGetNode(dock_up_id);
        node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

        ImGui::DockBuilderFinish(dock_main_id);
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGuiWindowFlags host_window_flags = 0;
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("DeepsEngine", nullptr, host_window_flags);
    ImGui::PopStyleVar(3);
    ImGui::DockSpace(dockspaceID, ImGui::GetIO().DisplaySize, dockspaceFlags);
    ImGui::End();

    ImGuiWindowFlags scene_window_flags = 0;
    scene_window_flags |= ImGuiWindowFlags_NoCollapse;
    if(ImGui::Begin("Scene", nullptr, scene_window_flags)) {
        if(ImGui::BeginChild("Test")) {
            ImGui::Text("txt");
            ImGui::EndChild();
        }
        ImGui::End();
    }

    ImGuiWindowFlags actions_window_flags = 0;
    actions_window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
    if(ImGui::Begin("Actions", nullptr, actions_window_flags)) {
        if (Application::getInstance().playing) {
            if (ImGui::Button("Stop")) { // Buttons return true when clicked (most widgets return true when edited/activated)
                Application::getInstance().setCursorMode(DeepsEngine::Cursor::CURSOR_NORMAL);
                Application::getInstance().playing = false;
            }
        } else {
            if (ImGui::Button("Play")) { // Buttons return true when clicked (most widgets return true when edited/activated)
                Application::getInstance().setCursorMode(DeepsEngine::Cursor::CURSOR_DISABLED);
                Application::getInstance().playing = true;
            }
        }
        ImGui::End();
    }

    ImGuiWindowFlags renderer_window_flags = 0;
    renderer_window_flags |= ImGuiWindowFlags_NoScrollbar;
    if(ImGui::Begin("Renderer", nullptr, renderer_window_flags))
    {
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        float width = vMax.x - vMin.x;
        float height = vMax.y - vMin.y;
        SCR_WIDTH = floor(width);
        SCR_HEIGHT = floor(height);
        ImGui::Image(reinterpret_cast<ImTextureID>(textureColorbuffer), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    if(ImGui::Begin("Inspector")) {
        if(ImGui::BeginChild("Test")) {
            ImGui::Text("txt");
            ImGui::EndChild();
        }
        ImGui::End();
    }

    if(ImGui::Begin("Console")) {
        if(ImGui::BeginChild("Test")) {
            ImGui::Text("txt");
            ImGui::EndChild();
        }
        ImGui::End();
    }

    if (defaultFont) {
        ImGui::PopFont();
    }

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
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

void OpenGLRenderer::setDefaultEditorFont(ImFont* font) {
    this->defaultFont = font;
}

void OpenGLRenderer::deinit() {
#if !(defined(EMSCRIPTEN) or (DEVELOP_WEB))
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