//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "src/Engine/component/Components.h"

void Scene::createEntity() {
    // create entity
    auto* entity = new Entity(this);

    Components::transform transform = {Components::position({0, 0, 0}),
                                       Components::rotation({0, 0, 0}),
                                       Components::scale({1, 1, 1})};

    entity->AddComponent<Components::transform>(transform);
}