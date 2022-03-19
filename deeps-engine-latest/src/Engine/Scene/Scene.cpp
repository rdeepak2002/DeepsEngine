//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "src/Engine/component/Component.h"

namespace DeepsEngine {
    void Scene::createEntity() {
        // create entity
        auto* entity = new Entity(this);

        DeepsEngine::Transform transform = {DeepsEngine::Position({0, 0, 0}),
                                            DeepsEngine::Rotation({0, 0, 0}),
                                            DeepsEngine::Scale({1, 1, 1})};

        entity->AddComponent<DeepsEngine::Transform>(transform);
    }
}