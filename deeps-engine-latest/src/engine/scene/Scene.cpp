//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "src/engine/component/Component.h"

namespace DeepsEngine {
    DeepsEngine::Entity Scene::CreateEntity(const std::string& name) {
        // create entity
//        std::shared_ptr<DeepsEngine::Entity> entityPtr(new DeepsEngine::Entity(this));
        DeepsEngine::Entity entity = {this};

        // add transform component
        Component::Transform transform = {Component::Position({0, 0, 0}),
                                          Component::Rotation({0, 0, 0}),
                                          Component::Scale({1, 1, 1})};
        entity.AddComponent<Component::Transform>(transform);

        // add tag component
        Component::Tag tag = {name.empty() ? "Entity" : name};
        entity.AddComponent<DeepsEngine::Component::Tag>(tag);

        // add id component
        Component::Id id = {entity.GetId()};
        entity.AddComponent<DeepsEngine::Component::Id>(id);

        return entity;
    }

    DeepsEngine::Entity Scene::CreateEntity() {
        return CreateEntity("");
    }

    void Scene::DestroyEntity(Entity entity) {
        entity.Destroy();
    }

    std::vector<DeepsEngine::Entity> Scene::GetEntities() {
        // get all entities in the ecs that have a Transform component
        auto entityHandles = registry.view<DeepsEngine::Component::Transform>();
        std::vector<DeepsEngine::Entity> arr;

        for(auto entityHandle : entityHandles) {
            DeepsEngine::Entity entity = {this, entityHandle};
            arr.push_back(entity);
        }

        return arr;
    }
}