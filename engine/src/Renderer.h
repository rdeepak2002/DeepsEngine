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

static int scrWidth = 800;
static int scrHeight = 600;

class Renderer {
private:
    std::string projectPath;
    bool showWindow;
    bool saveOutputRender;
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    Shader *ourShader;
public:
    Renderer(bool showWindow, bool saveOutputRender, std::string projectPath) {
        this->showWindow = showWindow;
        this->saveOutputRender = saveOutputRender;
        this->projectPath = projectPath;
    }

    GLFWwindow *window;

    std::string cachedFrame;

//    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void saveImage();

    int init(); // creates window/context
    void render(); //performs actual drawing
    bool shuttingDown();

    void shutDown();

    void processInput(GLFWwindow *window);

    void handleEditorResize(int width, int height);

    ~Renderer() {
        delete ourShader;
        ourShader = nullptr;
    }
};


#endif //ADDON_RENDERER_H
