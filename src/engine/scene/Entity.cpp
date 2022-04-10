//
// Created by Deepak Ramalingam on 3/19/22.
//

#include "Entity.h"

namespace DeepsEngine {
    Entity::Entity(Scene* sceneHandle)
            : scene(sceneHandle)
    {
        entity = scene->registry.create();
    }

    Entity::Entity(Scene* sceneHandle, entt::entity entityHandle)
            : scene(sceneHandle), entity(entityHandle)
    {

    }
}