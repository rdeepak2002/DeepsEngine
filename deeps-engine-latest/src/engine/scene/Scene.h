//
// Created by Deepak Ramalingam on 3/18/22.
//
#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include "src/engine/include/entt.hpp"
#include <iostream>

namespace DeepsEngine {
    class Entity;

    class Scene {
    public:
        entt::registry registry;
        std::shared_ptr<DeepsEngine::Entity> CreateEntity(const std::string& name);
        std::shared_ptr<DeepsEngine::Entity> CreateEntity();
        std::vector<std::shared_ptr<DeepsEngine::Entity>> GetEntities();
        void DestroyEntity(Entity* entity);
    };
}

#endif //EDITOR_SCENE_H
