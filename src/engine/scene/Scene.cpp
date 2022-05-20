//
// Created by Deepak Ramalingam on 3/18/22.
//

#include "Scene.h"
#include "Component.h"
#include "Uuid.h"

namespace DeepsEngine {
    DeepsEngine::Entity Scene::CreateEntity(std::string name, std::string guid) {
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
        entity.AddComponent<DeepsEngine::Component::Id>(guid);

        // make entity child of root by default
        entity.AddComponent<DeepsEngine::Component::HierarchyComponent>(entity);

        return entity;
    }

    DeepsEngine::Entity Scene::CreateEntity(std::string name) {
        return CreateEntity(name, uuid::generate_uuid_v4());
    }

    DeepsEngine::Entity Scene::CreateEntity() {
        return CreateEntity("", uuid::generate_uuid_v4());
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

    std::tuple<std::vector<DeepsEngine::Entity>, std::vector<DeepsEngine::Entity>> Scene::GetMeshEntities() {
        // get all entities in the ecs that have a Transform component
        auto entityHandles = registry.view<DeepsEngine::Component::MeshFilter, DeepsEngine::Component::Transform>();
        std::vector<DeepsEngine::Entity> staticMeshEntities, animatedMeshEntities;

        for (auto entityHandle : entityHandles) {
            DeepsEngine::Entity entity = {entityHandle};

            if (entity.GetComponent<Component::MeshFilter>().mesh == "animated-model") {
                animatedMeshEntities.push_back(entity);
            } else {
                staticMeshEntities.push_back(entity);
            }
        }

        return {staticMeshEntities, animatedMeshEntities};
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

    Entity& Scene::findEntityByGuid(std::string guid) {
        // TODO: make this faster by looking up in map of entity guids
        Entity* returnEntity = nullptr;

        registry.each([&](entt::entity entityHandle) {
            auto* entity = new Entity(entityHandle);

            if (entity->HasComponent<Component::Id>() && entity->GetComponent<Component::Id>().id == guid) {
                returnEntity = entity;
            }
        });

        if (!returnEntity) {
            Logger::Error("Entity not found for id " + guid);
            exit(1);
        }

        return *returnEntity;
    }

    bool Scene::entityExists(std::string guid) {
        bool result = false;

        // TODO: make this faster by looking up in map of entity guids
        registry.each([&](entt::entity entityHandle) {
            DeepsEngine::Entity entity = {entityHandle};

//            Logger::Debug("Found entity with id: " + entity.GetComponent<Component::Id>().id);

            if (entity.HasComponent<Component::Id>() && entity.GetComponent<Component::Id>().id == guid) {
                result = true;
            }
        });

        return result;
    }
}