//
// Created by Deepak Ramalingam on 3/19/22.
//

#include "Entity.h"
#include "Component.h"

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
    }
}