//
// Created by Deepak Ramalingam on 3/19/22.
//

#include "Entity.h"

namespace DeepsEngine {
    Entity::Entity(Scene* scene) {
        entity = scene->registry.create();
    }

    Entity::Entity(entt::entity entityHandle) : entity(entityHandle)
    {

    }
}