//
// Created by Deepak Ramalingam on 3/19/22.
//

#include "Entity.h"

Entity::Entity(Scene* sceneHandle)
        : scene(sceneHandle)
{
    entity = scene->registry.create();
}