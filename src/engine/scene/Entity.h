//
// Created by Deepak Ramalingam on 3/19/22.
//

#ifndef EDITOR_ENTITY_H
#define EDITOR_ENTITY_H

#include "src/engine/include/entt.hpp"
#include "Scene.h"

namespace DeepsEngine {
    class Entity {
    public:
        Entity() = default;
        Entity(Scene* scene);
        Entity(Scene* sceneHandle, entt::entity entityHandle);
        Entity(const Entity& other) = default;
        bool scriptOnCreateInvoked;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            // TODO: assert entity does not already have a component
            T& component = scene->registry.emplace<T>(entity, std::forward<Args>(args)...);
            // TODO: callback for when component added
            return component;
        }

        template<typename T>
        T& GetComponent() {
            // TODO: assert component exists
            return scene->registry.get<T>(entity);
        }

        void Destroy() {
            scene->registry.destroy(entity);
        }

        template<typename T>
        bool HasComponent() {
            // TODO: test this
            if (auto *comp = scene->registry.try_get<T>(entity)) {
                return true;
            } else {
                return false;
            }
        }

        template<typename T>
        void RemoveComponent() {
            // TODO: assert entity has component
            scene->registry.remove<T>(entity);
        }

        uint32_t GetId() {
            return static_cast<uint32_t>(entity);
        }

        Scene* GetScene() {
            return scene;
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
    private:
        entt::entity entity{entt::null};
        Scene* scene = nullptr;
    };

}

#endif //EDITOR_ENTITY_H
