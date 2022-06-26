//
// Created by Deepak Ramalingam on 6/20/22.
//

#include "SpinningEntity.hpp"
#include "Component.h"

void SpinningEntity::init() {
    NativeScript::init();
    std::cout << "test init" << std::endl;
}

void SpinningEntity::update(DeepsEngine::Entity& entity, double dt) {
    NativeScript::update(entity, dt);
//    std::cout << "test update entity " << entity.GetId() << std::endl;
    entity.GetComponent<DeepsEngine::Component::Transform>().rotation.y += 0.01 * dt;
}
