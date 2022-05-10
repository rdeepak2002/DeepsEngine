//
// Created by Deepak Ramalingam on 3/19/22.
//

#include "Entity.h"
#include "Component.h"

namespace DeepsEngine {
    Entity::Entity(Scene* scene) {
        entity = scene->registry.create();
    }

    Entity::Entity(entt::entity entityHandle) : entity(entityHandle)
    {

    }

    void Entity::Serialize(YAML::Emitter &out) {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << std::to_string(GetComponent<DeepsEngine::Component::Id>().id);

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

        out << YAML::EndMap;
    }
}