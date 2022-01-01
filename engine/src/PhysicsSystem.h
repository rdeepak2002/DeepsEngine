//
// Created by Deepak Ramalingam on 12/30/21.
//

#ifndef CORE_PHYSICSSYSTEM_H
#define CORE_PHYSICSSYSTEM_H

#include "System.h"
#include "Coordinator.h"

extern Coordinator gCoordinator;

class PhysicsSystem: public System {
public:
    void Update(float dt) {
        for (auto const& entity : mEntities)
        {
            auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
            auto& transform = gCoordinator.GetComponent<Transform>(entity);
            auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

            // TODO: fix operators
//            rigidBody.velocity += gravity.force * dt;
//            transform.position += rigidBody.velocity * dt;
        }
    }
};


#endif //CORE_PHYSICSSYSTEM_H
