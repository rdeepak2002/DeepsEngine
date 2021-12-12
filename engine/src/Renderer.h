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

class Renderer {
private:
    std::string projectPath;
    bool showWindow;
    bool saveOutputRender;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
//    unsigned int shaderProgram;
    unsigned int VBO, VAO;
//    const char *vertexShaderSource = "#version 330 core\n"
//                                     "layout (location = 0) in vec3 aPos;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                     "}\0";
//    const char *fragmentShaderSource = "#version 330 core\n"
//                                       "out vec4 FragColor;\n"
//                                       "void main()\n"
//                                       "{\n"
//                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                       "}\n\0";
public:
    Renderer(bool showWindow, bool saveOutputRender, std::string projectPath) {
        this->showWindow = showWindow;
        this->saveOutputRender = saveOutputRender;
        this->projectPath = projectPath;
    }

    GLFWwindow *window;

    std::string cachedFrame;

    void saveImage();

    int init(); // creates window/context
    void render(); //performs actual drawing
    bool shuttingDown();

    void shutDown();

    void processInput(GLFWwindow *window);

    ~Renderer() {}
};


#endif //ADDON_RENDERER_H
