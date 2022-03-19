//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "src/engine/component/Component.h"

namespace DeepsEngine {
    void Scene::createEntity() {
        // create entity
        auto* entity = new Entity(this);

        DeepsEngine::Component::Transform transform = {DeepsEngine::Component::Position({0, 0, 0}),
                                                       DeepsEngine::Component::Rotation({0, 0, 0}),
                                                       DeepsEngine::Component::Scale({1, 1, 1})};

        entity->AddComponent<DeepsEngine::Component::Transform>(transform);
    }


}