//
// Created by Deepak Ramalingam on 11/14/21.
//

#ifndef ADDON_RENDERER_H
#define ADDON_RENDERER_H

#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Shader.h"
#include "Component.h"
#include "ComponentSystem.h"
#include <stdio.h>
//#include "uuid.h"

static int scrWidth = 800;
static int scrHeight = 600;
static bool updateScreenSize = false;

class Renderer {
private:
    FILE *avconv = NULL;
    std::string projectPath;
    bool showWindow;
    bool saveOutputRender;
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    Shader *ourShader;
    std::map<std::string, std::string> entities;                 // map of <entityId, entityName>
    std::map<std::string, Component*> components;                // map of <entity (id), componentObj>
    std::map<std::string, ComponentSystem*> componentSystems;    // map of <componentName, componentSystem>
//    std::vector<int[3]> cubePositions;
//    float cubePositions[10][3] = {
//            { 0.0f, 0.0f,  0.0f },
//            { 2.0f, 5.0f, -15.0f },
//            { -1.5f, -2.2f, -2.5f },
//            { -3.8f, -2.0f, -12.3f },
//            { 2.4f, -0.4f, -3.5f },
//            { -1.7f, 3.0f, -7.5f },
//            {  1.3f, -2.0f, -2.5f },
//            { 1.5f, 2.0f, -2.5f },
//            { 1.5f, 0.2f, -1.5f },
//            { -1.3f, 1.0f, -1.5f }
//    };
public:
    GLFWwindow *window;
    std::string cachedFrame;

    Renderer(bool showWindow, bool saveOutputRender, std::string projectPath) {
        this->showWindow = showWindow;
        this->saveOutputRender = saveOutputRender;
        this->projectPath = projectPath;
    }

    ~Renderer() {
        delete ourShader;
        ourShader = nullptr;
        // TODO: free component system
    }

    void saveImage();
    int init(); // creates window/context
    void render(); //performs actual drawing
    bool shuttingDown();
    void shutDown();
    void processInput(GLFWwindow *window);
    void handleEditorResize(int width, int height);
    void addComponentSystem(ComponentSystem*);
    std::string addEntity(std::string name);
    void addComponent(Component*);
};


#endif //ADDON_RENDERER_H
