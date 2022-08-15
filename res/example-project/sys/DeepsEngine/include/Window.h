//
// Created by Deepak Ramalingam on 5/11/22.
//

#ifndef DEEPSENGINE_WINDOW_H
#define DEEPSENGINE_WINDOW_H

namespace DeepsEngine {
    namespace Cursor {
        enum CURSOR_TYPE {
            CURSOR_NORMAL = GLFW_CURSOR_NORMAL,
            CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN,
            CURSOR_DISABLED = GLFW_CURSOR_DISABLED
        };
    }
}

class Window {
public:
    virtual void createWindow() {

    }
    virtual bool shouldCloseWindow() {
        return false;
    }
    virtual void closeWindow() {

    }
    virtual void processInput() {

    }
    virtual void swapBuffers() {

    }
    virtual void pollEvents() {

    }
    virtual void setCursorMode(DeepsEngine::Cursor::CURSOR_TYPE cursor) {

    }
};

#endif //DEEPSENGINE_WINDOW_H
