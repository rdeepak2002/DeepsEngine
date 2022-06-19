//
// Created by Deepak Ramalingam on 6/11/22.
//

#include <iostream>
#include "NativeScriptComponent.hpp"

#define CLASS_NAME SpinningEntity

extern "C" {
class CLASS_NAME : public NativeScriptComponent {
public:
    void init() {
        NativeScriptComponent::init();
        std::cout << "test " << std::endl;
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
