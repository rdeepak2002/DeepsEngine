//
// Created by Deepak Ramalingam on 11/14/21.
//

#include "Renderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define GetCurrentDir getcwd

void Renderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    //If you press ESC and set windowShouldClose to True, the external loop will close the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    std::cout << "ESC" << mode;
}

std::string Renderer::get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

void Renderer::saveImage(char *filepath, GLFWwindow *w) {
    int width, height;
    glfwGetFramebufferSize(w, &width, &height);
    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * height;
    std::vector<char> buffer(bufferSize);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    stbi_flip_vertically_on_write(true);
    stbi_write_png(filepath, width, height, nrChannels, buffer.data(), stride);
//    printf("exported frame to %s/%s\n", get_current_dir().c_str(), filepath);
}

void Renderer::startNewThread(void) {
    std::thread( [this] { test(); } ).detach();
}

void Renderer::test(void) {
    int i = 0;
    while (1) {
        printf("called within thread %d\n", i);
        i++;
    }
}

int Renderer::startOpenGL(void) {
    //Initialize GLFW Library
    if (!glfwInit())
        return -1;
    //Create window and context
    GLFWwindow *window = glfwCreateWindow(640, 480, "hello world", NULL, NULL);
    if (!window) {
        //NULL will be returned if creation fails
        glfwTerminate();
    }
    //Establish the context of the current window
    glfwMakeContextCurrent(window);

//    glfwSetKeyCallback(window, this->key_callback); //Registering Callbacks

    float trapezoidColor = 0.5;

    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        /*******Polling events*******/
        glfwPollEvents();

        /*******Rendering*******/
        //Select empty color RGBA
        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //Start drawing a triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); //Red
        glVertex3f(0, 1, 1);

        glColor3f(0, 1, 0); //Green
        glVertex3f(-1, -1, 0);

        glColor3f(0, 0, 1); //Blue
        glVertex3f(1, -1, 0);
        //End a drawing step
        glEnd();

        glBegin(GL_POLYGON);
        //Draw another trapezoid, and pay attention to the stroke order
        glColor3f(trapezoidColor, trapezoidColor, trapezoidColor); //Grey
        glVertex2d(0.5, 0.5);
        glVertex2d(1, 1);
        glVertex2d(1, 0);
        glVertex2d(0.5, 0);
        glEnd();

        // change trapezoid color
        trapezoidColor += 0.05;

        if (trapezoidColor > 1) {
            trapezoidColor = 0;
        }

        // save frame to image file
        saveImage("frame.png", window);

        printf("OpenGL saved frame\n");

        /******Exchange buffer, update content on window******/
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}