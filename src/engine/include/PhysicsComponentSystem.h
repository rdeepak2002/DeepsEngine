//
// Created by Deepak Ramalingam on 7/16/22.
//

#ifndef DEEPSENGINE_PHYSICSCOMPONENTSYSTEM_H
#define DEEPSENGINE_PHYSICSCOMPONENTSYSTEM_H

#include "ComponentSystem.h"
#include "btBulletDynamicsCommon.h"
#include "BulletDebugDrawer_OpenGL.h"

class PhysicsComponentSystem : public ComponentSystem {
public:
    PhysicsComponentSystem() = default;
    void init() override;
    void destroy() override;
    void update(float deltaTime) override;
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
//    btDiscreteDynamicsWorld* dynamicsWorld;
};

#endif //DEEPSENGINE_PHYSICSCOMPONENTSYSTEM_H
