//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Components.h"

void Scene::createEntity() {
    // create entity
    auto entity = registry.create();
    Components::transform transform = {Components::position({0, 0, 0}),
                                       Components::rotation({0, 0, 0}),
                                       Components::scale({1, 1, 1})};
    registry.emplace_or_replace<Components::transform>(entity, transform);
}