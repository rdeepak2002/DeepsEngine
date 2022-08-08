//
// Created by Deepak Ramalingam on 6/20/22.
//

#pragma once

#ifndef NATIVE_SPINNINGENTITY_HPP
#define NATIVE_SPINNINGENTITY_HPP

#include <iostream>
#include "NativeScript.h"

#define CLASS_NAME PlayerController

extern "C" class CLASS_NAME : public NativeScript {
private:
    float speed = 8.0f;
    float jumpSpeedReductionFactor = 0.7f;
    float jumpSpeed = 9.0f;
    float rotationSpeed = 5.0f;
    std::string currentState = "Idle";
    Animation* idleAnimation;
    Animation* runningAnimation;
public:
    CLASS_NAME(DeepsEngine::Entity &entity) : NativeScript(entity) {

    }
    void init() override;
    void update(double dt) override;
};

extern "C" NativeScript* CREATE_FUNC(CLASS_NAME)(DeepsEngine::Entity& entity) {
    return new CLASS_NAME(entity);
}

extern "C" void DESTROY_FUNC(CLASS_NAME)(NativeScript* p) {
    delete p;
}

#endif //NATIVE_SPINNINGENTITY_HPP
