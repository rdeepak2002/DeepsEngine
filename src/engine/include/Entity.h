//
// Created by Deepak Ramalingam on 3/19/22.
//

#ifndef EDITOR_ENTITY_H
#define EDITOR_ENTITY_H

#include <yaml-cpp/emitter.h>
#include "Scene.h"
#include "OpenGLRenderer.h"
#include "Application.h"
#include "entt/entt.hpp"

namespace DeepsEngine {
    class Entity {
    public:
        Entity() = default;
        Entity(Scene* scene);
        Entity(entt::entity entityHandle);
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            // TODO: assert entity does not already have a component
            T& component = Application::getInstance().scene.registry.emplace<T>(entity, std::forward<Args>(args)...);
            // TODO: callback for when component added
            return component;
        }

        template<typename T>
        T& GetComponent() const {
            // TODO: assert component exists
            return Application::getInstance().scene.registry.get<T>(entity);
        }

        void Destroy() {
            Application::getInstance().scene.registry.destroy(entity);
        }

        template<typename T>
        bool HasComponent() const {
            // TODO: test this
            if (auto *comp = Application::getInstance().scene.registry.try_get<T>(entity)) {
                return true;
            } else {
                return false;
            }
        }

        bool IsValid() {
            return Application::getInstance().scene.registry.valid(entity);
        }

        template<typename T>
        void RemoveComponent() {
            // TODO: assert entity has component
            Application::getInstance().scene.registry.remove<T>(entity);
        }

        void Serialize(YAML::Emitter &out) const;

        void Deserialize(YAML::Node entityYaml);

        uint32_t GetId() {
            return static_cast<uint32_t>(entity);
        }

        operator entt::entity() const {
            return entity;
        }

        operator bool() const {
            return entity != entt::null;
        }

        bool operator==(Entity& other)
        {
            return GetId() == other.GetId();
        }

        bool operator!=(Entity& other)
        {
            return GetId() != other.GetId();
        }

        operator std::string() const {
            YAML::Emitter out;
            Serialize(out);
            return out.c_str();
        }
    private:
        entt::entity entity{entt::null};
    };

}

#endif //EDITOR_ENTITY_H
