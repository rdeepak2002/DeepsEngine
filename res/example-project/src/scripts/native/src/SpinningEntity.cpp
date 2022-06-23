//
// Created by Deepak Ramalingam on 6/20/22.
//

#include "SpinningEntity.hpp"

void SpinningEntity::init() {
    NativeScript::init();
    std::cout << "test init" << std::endl;
}

void SpinningEntity::update(double dt) {
    NativeScript::update(dt);
    std::cout << "test update" << std::endl;
}
