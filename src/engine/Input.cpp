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
    return Input::getInstance().mousePosition;
}

void Input::SetMousePosition(double x, double y) {
    Input::getInstance().mousePosition = {x, y};
}

glm::vec2 Input::GetMouseMovement() {
    return Input::getInstance().mouseMovement;
}

void Input::SetMouseMovement(double x, double y) {
    Input::getInstance().mouseMovement = {x, y};
}
