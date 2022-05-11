//
// Created by Deepak Ramalingam on 5/11/22.
//

#ifndef DEEPSENGINE_WINDOW_H
#define DEEPSENGINE_WINDOW_H

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
};

#endif //DEEPSENGINE_WINDOW_H
