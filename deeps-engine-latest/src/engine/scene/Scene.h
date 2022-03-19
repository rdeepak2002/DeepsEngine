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
        DeepsEngine::Entity CreateEntity(const std::string& name);
        DeepsEngine::Entity CreateEntity();
        std::vector<DeepsEngine::Entity> GetEntities();
        void DestroyEntity(DeepsEngine::Entity entity);
    };
}

#endif //EDITOR_SCENE_H
