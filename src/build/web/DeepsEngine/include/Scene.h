//
// Created by Deepak Ramalingam on 3/18/22.
//
#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include <entt/entt.hpp>
#include <iostream>

namespace DeepsEngine {
    class Entity;

    class Scene {
    public:
        entt::registry registry;
        DeepsEngine::Entity CreateEntity(const std::string& name);
        DeepsEngine::Entity CreateEntity();
        std::vector<DeepsEngine::Entity> GetEntities();
        std::vector<DeepsEngine::Entity> GetDrawableEntities();
        std::vector<DeepsEngine::Entity> GetScriptableEntities();
        std::vector<DeepsEngine::Entity> GetCameraEntities();
        void DestroyEntity(DeepsEngine::Entity entity);
    };
}

#endif //EDITOR_SCENE_H
