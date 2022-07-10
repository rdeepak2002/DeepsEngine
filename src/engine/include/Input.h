//
// Created by Deepak Ramalingam on 5/1/22.
//

#ifndef EDITOR_INPUT_H
#define EDITOR_INPUT_H

#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>

class Input {
public:
    static Input& getInstance()
    {
        static Input instance;
        return instance;
    }
    static bool GetButtonDown(int keyCode);
    static void SetButtonDown(int keyCode, bool state);

    static glm::vec2 GetMousePosition();
    static void SetMousePosition(double x, double y);

    static glm::vec2 GetMouseMovement();
    static void SetMouseMovement(double x, double y);
private:
    Input() {}
    std::unordered_map<int, bool> keyDownMap;
    glm::vec2 mousePosition;
    glm::vec2 mouseMovement;
public:
    Input(Input const&) = delete;
    void operator=(Input const&) = delete;
};


#endif //EDITOR_INPUT_H
