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
#include "Shader.h"

class Renderer {
private:
    GLFWwindow *window;
    float trapezoidColor;
public:
    void saveImage(char *filepath);
    Renderer(void) {
        trapezoidColor = 0.5;
    }
//    virtual void addEntity(entity* e) = 0;
//    virtual void removeEntity(entity* e) = 0;
//    virtual void clearAllEntities(void) = 0;
     void init(void); // creates window/context
     void render(void); //performs actual drawing
     bool shuttingDown(void);
     void shutDown(void);
     void pollEvents(void);
     ~Renderer(void) { }
};


#endif //ADDON_RENDERER_H
