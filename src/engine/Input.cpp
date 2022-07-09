//
// Created by Deepak Ramalingam on 5/1/22.
//

#include "Input.h"

bool Input::GetButtonDown(int keyCode) {
    if (Input::getInstance().keyDownMap.find(keyCode) == Input::getInstance().keyDownMap.end()) {
        return false;
    }

    return Input::getInstance().keyDownMap[keyCode];
}

void Input::SetButtonDown(int keyCode, bool state) {
    Input::getInstance().keyDownMap[keyCode] = state;
}

glm::vec2 Input::GetMousePosition() {
    return {float(Input::getInstance().mouseX), float(Input::getInstance().mouseY)};
}

void Input::SetMousePosition(double x, double y) {
    Input::getInstance().mouseX = x;
    Input::getInstance().mouseY = y;
}
