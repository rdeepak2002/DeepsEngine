//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "src/engine/component/Component.h"

namespace DeepsEngine {
    std::shared_ptr<DeepsEngine::Entity> Scene::CreateEntity(const std::string& name) {
        // create entity
        std::shared_ptr<DeepsEngine::Entity> entityPtr(new DeepsEngine::Entity(this));


        // add transform component
        Component::Transform transform = {Component::Position({0, 0, 0}),
                                          Component::Rotation({0, 0, 0}),
                                          Component::Scale({1, 1, 1})};
        entityPtr->AddComponent<Component::Transform>(transform);

        // add tag component
        Component::Tag tag = {name.empty() ? "Entity" : name};
        entityPtr->AddComponent<DeepsEngine::Component::Tag>(tag);

        // add id component
        Component::Id id = {entityPtr->GetId()};
        entityPtr->AddComponent<DeepsEngine::Component::Id>(id);

        return entityPtr;
    }

    std::shared_ptr<DeepsEngine::Entity> Scene::CreateEntity() {
        return CreateEntity("");
    }

    void Scene::DestroyEntity(Entity* entity) {
        entity->Destroy();
    }

    std::vector<std::shared_ptr<DeepsEngine::Entity>> Scene::GetEntities() {
        // get all entities in the ecs that have a Transform component
        auto entityHandles = registry.view<DeepsEngine::Component::Transform>();
        std::vector<std::shared_ptr<DeepsEngine::Entity>> arr;

        for(auto entityHandle : entityHandles) {
            std::shared_ptr<DeepsEngine::Entity> entityPtr(new DeepsEngine::Entity(this, entityHandle));
            arr.push_back(entityPtr);
        }

        return arr;
    }
}