//
// Created by Deepak Ramalingam on 11/14/21.
//

#ifndef ADDON_RENDERER_H
#define ADDON_RENDERER_H

#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
//#include "Shader.h"

class Renderer {
private:
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    unsigned int shaderProgram;
    unsigned int VBO, VAO;
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
public:
    Renderer(void) { }
    GLFWwindow *window;
    void saveImage(char *filepath);
    int init(void); // creates window/context
    void render(void); //performs actual drawing
    bool shuttingDown(void);
    void shutDown(void);
    void processInput(GLFWwindow *window);
    ~Renderer(void) { }
};


#endif //ADDON_RENDERER_H
