//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Entity.h"
#include "Component.h"

namespace DeepsEngine {
    DeepsEngine::Entity Scene::CreateEntity(const std::string& name) {
        // create entity
        DeepsEngine::Entity entity = {this};

        // add transform component
        Component::Transform transform = {glm::vec3(0, 0, 0),
                                          glm::vec3(0, 0, 0),
                                          glm::vec3(1, 1, 1)};
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
        // TODO: call function callback
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
            DeepsEngine::Entity entity = {entityHandle};
            arr.push_back(entity);
        }

        return arr;
    }

    std::vector<DeepsEngine::Entity> Scene::GetDrawableEntities() {
        // get all entities in the ecs that have a Transform component
        auto entityHandles = registry.view<DeepsEngine::Component::MeshFilter>();
        std::vector<DeepsEngine::Entity> arr;

        for (auto entityHandle : entityHandles) {
            DeepsEngine::Entity entity = {entityHandle};

            if (entity.HasComponent<DeepsEngine::Component::Transform>()) {
                arr.push_back(entity);
            }
        }

        return arr;
    }

    std::tuple<std::vector<DeepsEngine::Entity>, std::vector<DeepsEngine::Entity>, std::vector<DeepsEngine::Entity>> Scene::GetLightEntities() {
        // get all entities in the ecs that have a light component
        auto entityHandles = registry.view<DeepsEngine::Component::Light>();
        std::vector<DeepsEngine::Entity> directionalLights, pointLights, spotLights;

        for (auto entityHandle : entityHandles) {
            DeepsEngine::Entity entity = {entityHandle};

            std::string lightType = entity.GetComponent<Component::Light>().type;

            if (lightType == "directional") {
                directionalLights.push_back(entity);
            } else if (lightType == "point") {
                pointLights.push_back(entity);
            } else if (lightType == "spotlight") {
                spotLights.push_back(entity);
            } else {
                Logger::Error("Invalid light type detected in Light component: " + lightType);
            }
        }

        return {directionalLights, pointLights, spotLights};
    }

    std::vector<DeepsEngine::Entity> Scene::GetScriptableEntities() {
        // get all entities in the ecs that have a Transform component
        auto entityHandles = registry.view<DeepsEngine::Component::LuaScript>();
        std::vector<DeepsEngine::Entity> arr;

        for (auto entityHandle : entityHandles) {
            DeepsEngine::Entity entity = {entityHandle};
            arr.push_back(entity);
        }

        return arr;
    }

    std::vector<DeepsEngine::Entity> Scene::GetCameraEntities() {
        // get all entities in the ecs that have a Transform component
        auto entityHandles = registry.view<DeepsEngine::Component::Camera>();
        std::vector<DeepsEngine::Entity> arr;

        for (auto entityHandle : entityHandles) {
            DeepsEngine::Entity entity = {entityHandle};
            arr.push_back(entity);
        }

        return arr;
    }

    void Scene::DestroyAllEntities() {
        registry.each([&](entt::entity entity) {
            registry.destroy(entity);
        });
    }
}