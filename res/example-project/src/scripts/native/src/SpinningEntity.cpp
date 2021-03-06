//
// Created by Deepak Ramalingam on 6/20/22.
//

#include "SpinningEntity.hpp"
#include "Component.h"

void SpinningEntity::init() {
    NativeScript::init();
    Logger::Debug("Init spinning entity");
}

void SpinningEntity::update(double dt) {
    self.GetComponent<DeepsEngine::Component::Transform>().rotation.y += 0.1 * dt;
}
