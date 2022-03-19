//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "src/engine/component/Component.h"

namespace DeepsEngine {
    DeepsEngine::Entity* Scene::CreateEntity() {
        // create entity
        auto* entity = new DeepsEngine::Entity(this);

        // add transform component
        Component::Transform transform = {Component::Position({0, 0, 0}),
                                          Component::Rotation({0, 0, 0}),
                                          Component::Scale({1, 1, 1})};
        entity->AddComponent<Component::Transform>(transform);

        // add tag component
        Component::Tag tag = {"entity"};
        entity->AddComponent<DeepsEngine::Component::Tag>(tag);

        // add id component
        Component::Id id = {entity->GetId()};
        entity->AddComponent<DeepsEngine::Component::Id>(id);

        return entity;
    }

    void Scene::DestroyEntity(Entity* entity) {
        entity->Destroy();
    }
}