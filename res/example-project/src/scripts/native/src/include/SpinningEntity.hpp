//
// Created by Deepak Ramalingam on 6/20/22.
//

#ifndef NATIVE_SPINNINGENTITY_HPP
#define NATIVE_SPINNINGENTITY_HPP

#include <iostream>
#include "NativeScriptComponent.hpp"

#define CLASS_NAME SpinningEntity

#include "NativeScriptComponent.hpp"

extern "C" {
class SpinningEntity : public NativeScriptComponent {
public:
    void init() {
        NativeScriptComponent::init();
        std::cout << "test 3.0" << std::endl;
    }
    void update(double dt) {
        NativeScriptComponent::update(dt);
    }
};
}

extern "C" NativeScriptComponent* CREATE_FUNC(CLASS_NAME)() {
    return new CLASS_NAME;
}

extern "C" void DESTROY_FUNC(CLASS_NAME)(NativeScriptComponent* p) {
    delete p;
}

#endif //NATIVE_SPINNINGENTITY_HPP
