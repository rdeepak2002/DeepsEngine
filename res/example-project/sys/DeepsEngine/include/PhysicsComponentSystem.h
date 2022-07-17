//
// Created by Deepak Ramalingam on 7/16/22.
//

#ifndef DEEPSENGINE_PHYSICSCOMPONENTSYSTEM_H
#define DEEPSENGINE_PHYSICSCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

class PhysicsComponentSystem : public ComponentSystem {
public:
    PhysicsComponentSystem() = default;
    void init() override;
    void destroy() override;
    void update(float deltaTime) override;
};

#endif //DEEPSENGINE_PHYSICSCOMPONENTSYSTEM_H
