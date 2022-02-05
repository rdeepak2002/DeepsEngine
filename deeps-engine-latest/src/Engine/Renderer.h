//
// Created by Deepak Ramalingam on 2/5/22.
//

#ifndef EXAMPLE_RENDERER_H
#define EXAMPLE_RENDERER_H

#if defined(STANDALONE)
#include <glad.h>
#include <glfw3.h>
#else
#include <QOpenGLExtraFunctions>
#endif

#include "Shader.h"

#if defined(STANDALONE)
class Renderer {
#else
class Renderer: protected QOpenGLExtraFunctions {
#endif
public:
    #if defined(STANDALONE)
    void createWindow();
    #endif

    void initialize();
    void clear();
    void update();

#if defined(STANDALONE)
    bool shouldCloseWindow();
    void closeWindow();
#endif

#if defined(STANDALONE)
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    GLFWwindow* window;
#endif

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

    unsigned int shaderProgram;
    unsigned int VBO, VAO;

    Shader* ourShader;
};


#endif //EXAMPLE_RENDERER_H
//#include <QOpenGLExtraFunctions>
//
//namespace Renderer {
//    void initialize();
//    void update();
//}