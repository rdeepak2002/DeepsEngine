//
// Created by Deepak Ramalingam on 5/11/22.
//

#ifndef DEEPSENGINE_RENDERER_H
#define DEEPSENGINE_RENDERER_H

class Renderer {
public:
    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;

    virtual void initialize() {

    }
    virtual void deinit() {

    }
    virtual void clear() {

    }
    virtual void update() {

    }
};

#endif //DEEPSENGINE_RENDERER_H
