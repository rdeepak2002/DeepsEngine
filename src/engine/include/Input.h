//
// Created by Deepak Ramalingam on 5/1/22.
//

#ifndef EDITOR_INPUT_H
#define EDITOR_INPUT_H

#include <iostream>
#include <unordered_map>

class Input {
public:
    static Input& getInstance()
    {
        static Input instance;
        return instance;
    }
    static bool GetButtonDown(int keyCode);
    static void SetButtonDown(int keyCode, bool state);
private:
    Input() {}
    std::unordered_map<int, bool> keyDownMap;
    double mouseMoveX, mouseMoveY;
    double mouseX, mouseY;
public:
    Input(Input const&) = delete;
    void operator=(Input const&) = delete;
};


#endif //EDITOR_INPUT_H
