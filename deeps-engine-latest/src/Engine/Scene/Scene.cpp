//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "src/Engine/component/Components.h"

namespace DeepsEngine {
    void Scene::createEntity() {
        // create entity
        auto* entity = new Entity(this);

        Components::Transform transform = {Components::Position({0, 0, 0}),
                                           Components::Rotation({0, 0, 0}),
                                           Components::Scale({1, 1, 1})};

        entity->AddComponent<Components::Transform>(transform);
    }
}