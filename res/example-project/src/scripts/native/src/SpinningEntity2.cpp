//
// Created by Deepak Ramalingam on 6/28/22.
//

#include "SpinningEntity2.hpp"
#include "Component.h"

void SpinningEntity2::init() {
    NativeScript::init();
    Logger::Debug("Init spinning entity 2");
}

void SpinningEntity2::update(double dt) {
    self.GetComponent<DeepsEngine::Component::Transform>().rotation.y -= 0.1 * dt;
}
