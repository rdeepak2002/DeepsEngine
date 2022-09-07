//
// Created by Deepak Ramalingam on 5/11/22.
//

#ifndef DEEPSENGINE_RENDERER_H
#define DEEPSENGINE_RENDERER_H
#include <imgui.h>

class Renderer {
public:
    unsigned int SCR_WIDTH = 1600;
    unsigned int SCR_HEIGHT = 1200;

    virtual void initialize() {

    }
    virtual void deinit() {

    }
    virtual void clear() {

    }
    virtual void update() {

    }
    virtual unsigned int loadTexture(char const * path) {
        return 0;
    }
    virtual void updateFrameBuffer() {

    }
    virtual void setDefaultEditorFont(ImFont* font) {

    }
};

#endif //DEEPSENGINE_RENDERER_H
