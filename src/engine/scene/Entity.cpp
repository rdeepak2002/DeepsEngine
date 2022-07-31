//
// Created by Deepak Ramalingam on 3/19/22.
//

#include "Entity.h"
#include "Component.h"
#include <algorithm>

namespace DeepsEngine {
    Entity::Entity(Scene* scene) {
        entity = scene->registry.create();
    }

    Entity::Entity(entt::entity entityHandle) : entity(entityHandle) {

    }

    void Entity::Serialize(YAML::Emitter &out) const {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << GetComponent<DeepsEngine::Component::Id>().id;

        if (HasComponent<Component::Tag>()) {
            GetComponent<Component::Tag>().Serialize(out);
        }

        if (HasComponent<Component::Transform>()) {
            GetComponent<Component::Transform>().Serialize(out);
        }

        if (HasComponent<Component::MeshFilter>()) {
            GetComponent<Component::MeshFilter>().Serialize(out);
        }

        if (HasComponent<Component::Camera>()) {
            GetComponent<Component::Camera>().Serialize(out);
        }

        if (HasComponent<Component::LuaScript>()) {
            GetComponent<Component::LuaScript>().Serialize(out);
        }

        if (HasComponent<Component::Material>()) {
            GetComponent<Component::Material>().Serialize(out);
        }

        if (HasComponent<Component::Light>()) {
            GetComponent<Component::Light>().Serialize(out);
        }

        if (HasComponent<Component::HierarchyComponent>()) {
            GetComponent<Component::HierarchyComponent>().Serialize(out);
        }

        if (HasComponent<Component::NativeScriptComponent>()) {
            GetComponent<Component::NativeScriptComponent>().Serialize(out);
        }

        if (HasComponent<Component::SceneCameraComponent>()) {
            GetComponent<Component::SceneCameraComponent>().Serialize(out);
        }

        if (HasComponent<Component::PhysicsComponent>()) {
            GetComponent<Component::PhysicsComponent>().Serialize(out);
        }

        out << YAML::EndMap;
    }

    void Entity::Deserialize(YAML::Node entityYaml) {
        std::string entityId;

        if(entityYaml["Entity"]) {
            entityId = entityYaml["Entity"].as<std::string>();
            RemoveComponent<Component::Id>();
            AddComponent<Component::Id>(entityId);
        }

        if(entityYaml["Tag"]) {
            RemoveComponent<Component::Tag>();
            AddComponent<Component::Tag>(entityYaml["Tag"]);
        }

        if(entityYaml["Transform"]) {
            RemoveComponent<Component::Transform>();
            AddComponent<Component::Transform>(entityYaml["Transform"]);
        }

        if(entityYaml["MeshFilter"]) {
            RemoveComponent<Component::MeshFilter>();
            AddComponent<Component::MeshFilter>(entityYaml["MeshFilter"], entityId);
        }

        if(entityYaml["Camera"]) {
            RemoveComponent<Component::Camera>();
            AddComponent<Component::Camera>(entityYaml["Camera"]);
        }

        if(entityYaml["LuaScript"]) {
            RemoveComponent<Component::LuaScript>();
            AddComponent<Component::LuaScript>(entityYaml["LuaScript"]);
        }

        if(entityYaml["Material"]) {
            RemoveComponent<Component::Material>();
            AddComponent<Component::Material>(entityYaml["Material"]);
        }

        if(entityYaml["Light"]) {
            RemoveComponent<Component::Light>();
            AddComponent<Component::Light>(entityYaml["Light"]);
        }

        if(entityYaml["Hierarchy"]) {
            RemoveComponent<Component::HierarchyComponent>();
            AddComponent<Component::HierarchyComponent>(entityYaml["Hierarchy"], entityId);
        }

        if(entityYaml["NativeScriptComponent"]) {
            RemoveComponent<Component::NativeScriptComponent>();
            AddComponent<Component::NativeScriptComponent>(entityYaml["NativeScriptComponent"]);
        }

        if(entityYaml["SceneCamera"]) {
            RemoveComponent<Component::SceneCameraComponent>();
            AddComponent<Component::SceneCameraComponent>(entityYaml["SceneCamera"]);
        }

        if(entityYaml["PhysicsComponent"]) {
            RemoveComponent<Component::PhysicsComponent>();
            AddComponent<Component::PhysicsComponent>(entityYaml["PhysicsComponent"]);
        }
    }

    void Entity::Destroy() {
        if (HasComponent<Component::HierarchyComponent>()) {
            // delete children
            for (std::string childEntityGuid : GetComponent<Component::HierarchyComponent>().childrenGuids) {
                if (Application::getInstance().scene.entityExists(childEntityGuid)) {
                    Entity childEntity = Application::getInstance().scene.findEntityByGuid(childEntityGuid);
                    childEntity.Destroy();
                    Logger::Debug("Removed child entity: " + childEntityGuid);
                } else {
                    Logger::Warn("Could not find child entity: " + childEntityGuid);
                }
            }

            this->GetComponent<Component::HierarchyComponent>().childrenGuids.clear();

            // tell parent this entity is no longer a child
            std::string parentGuid = this->GetComponent<Component::HierarchyComponent>().parentGuid;
            std::string thisEntityGuid = GetComponent<Component::Id>().id;

            if (parentGuid != "root") {
                if (Application::getInstance().scene.entityExists(parentGuid)) {
                    Entity parentEntity = Application::getInstance().scene.findEntityByGuid(parentGuid);

                    if (parentEntity.HasComponent<Component::HierarchyComponent>()) {
                        std::vector<std::string> childrenGuids = parentEntity.GetComponent<Component::HierarchyComponent>().childrenGuids;

                        auto position = std::find(childrenGuids.begin(), childrenGuids.end(), thisEntityGuid);
                        if (position != childrenGuids.end()) {
                            childrenGuids.erase(position);
                        }

                        parentEntity.GetComponent<Component::HierarchyComponent>().childrenGuids = childrenGuids;
                    }
                } else {
                    Logger::Warn("Could not find parent entity: " + parentGuid);
                }
            }

            this->GetComponent<Component::HierarchyComponent>().parentGuid = "root";
        }

        Application::getInstance().scene.registry.destroy(entity);
    }

    // overload the operator<
    bool Entity::operator<(const Entity &r) const
    {
        return GetComponent<DeepsEngine::Component::Id>().id < r.GetComponent<DeepsEngine::Component::Id>().id;
    }

    // overload the operator> (if required)
    bool Entity::operator>(const Entity &r) const
    {
        return GetComponent<DeepsEngine::Component::Id>().id > r.GetComponent<DeepsEngine::Component::Id>().id;
    }
}