//
// Created by Deepak Ramalingam on 3/18/22.
//
#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include "src/engine/include/entt.hpp"

namespace DeepsEngine {
    class Scene {
    public:
        entt::registry registry;
        void createEntity();
    };
}

#endif //EDITOR_SCENE_H
