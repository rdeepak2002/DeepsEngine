//
// Created by Deepak Ramalingam on 6/20/22.
//

#pragma once

#ifndef NATIVE_SPINNINGENTITY_HPP
#define NATIVE_SPINNINGENTITY_HPP

#include <iostream>
#include "NativeScript.h"

#define CLASS_NAME MainCameraController

extern "C" class CLASS_NAME : public NativeScript {
private:

    float radius;
    float phi;
    float phiSpeed;
    float theta;
    float minTheta;
    float maxTheta;
    float thetaSpeed;
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
