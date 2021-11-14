//
// Created by Deepak Ramalingam on 11/14/21.
//

#ifndef ADDON_RENDERER_H
#define ADDON_RENDERER_H

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <thread>

class Renderer {
private:
public:
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
    std::string get_current_dir();
    void saveImage(char *filepath, GLFWwindow *w);
    void test(void);
    void startNewThread(void);
    int startOpenGL(void);
};


#endif //ADDON_RENDERER_H
