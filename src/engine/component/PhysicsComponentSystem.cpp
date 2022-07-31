//
// Created by Deepak Ramalingam on 7/16/22.
//

#include "PhysicsComponentSystem.h"
#include "Logger.h"
#include "Application.h"
#include "Entity.h"
#include "Component.h"

void PhysicsComponentSystem::init() {
    ComponentSystem::init();

//    Logger::Debug("Running physics stuff");
//
//    ///-----includes_end-----
//
//    int i;
//    ///-----initialization_start-----
//
//    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
//    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//
//    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
//    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
//
//    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
//    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
//
//    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
//    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
//
//    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
//
//    dynamicsWorld->setGravity(btVector3(0, -10, 0));
//
//    ///-----initialization_end-----
//
//    //keep track of the shapes, we release memory at exit.
//    //make sure to re-use collision shapes among rigid bodies whenever possible!
//    btAlignedObjectArray<btCollisionShape*> collisionShapes;
//
//    ///create a few basic rigid bodies
//
//    //the ground is a cube of side 100 at position y = -56.
//    //the sphere will hit it at y = -6, with center at -5
//    {
//        btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
//
//        collisionShapes.push_back(groundShape);
//
//        btTransform groundTransform;
//        groundTransform.setIdentity();
//        groundTransform.setOrigin(btVector3(0, -56, 0));
//
//        btScalar mass(0.);
//
//        //rigidbody is dynamic if and only if mass is non zero, otherwise static
//        bool isDynamic = (mass != 0.f);
//
//        btVector3 localInertia(0, 0, 0);
//        if (isDynamic)
//            groundShape->calculateLocalInertia(mass, localInertia);
//
//        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
//        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
//        btRigidBody* body = new btRigidBody(rbInfo);
//
//        //add the body to the dynamics world
//        dynamicsWorld->addRigidBody(body);
//    }
//
//    {
//        //create a dynamic rigidbody
//
//        //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
//        btCollisionShape* colShape = new btSphereShape(btScalar(1.));
//        collisionShapes.push_back(colShape);
//
//        /// Create Dynamic Objects
//        btTransform startTransform;
//        startTransform.setIdentity();
//
//        btScalar mass(1.f);
//
//        //rigidbody is dynamic if and only if mass is non zero, otherwise static
//        bool isDynamic = (mass != 0.f);
//
//        btVector3 localInertia(0, 0, 0);
//        if (isDynamic)
//            colShape->calculateLocalInertia(mass, localInertia);
//
//        startTransform.setOrigin(btVector3(2, 10, 0));
//
//        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
//        btRigidBody* body = new btRigidBody(rbInfo);
//
//        dynamicsWorld->addRigidBody(body);
//    }
//
//    /// Do some simulation
//
//    ///-----stepsimulation_start-----
//    for (i = 0; i < 150; i++)
//    {
//        dynamicsWorld->stepSimulation(1.f / 60.f, 10);
//
//        //print positions of all objects
//        for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
//        {
//            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
//            btRigidBody* body = btRigidBody::upcast(obj);
//            btTransform trans;
//            if (body && body->getMotionState())
//            {
//                body->getMotionState()->getWorldTransform(trans);
//            }
//            else
//            {
//                trans = obj->getWorldTransform();
//            }
//            printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
//        }
//    }
//
//    ///-----stepsimulation_end-----
//
//    //cleanup in the reverse order of creation/initialization
//
//    ///-----cleanup_start-----
//
//    //remove the rigidbodies from the dynamics world and delete them
//    for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
//    {
//        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
//        btRigidBody* body = btRigidBody::upcast(obj);
//        if (body && body->getMotionState())
//        {
//            delete body->getMotionState();
//        }
//        dynamicsWorld->removeCollisionObject(obj);
//        delete obj;
//    }
//
//    //delete collision shapes
//    for (int j = 0; j < collisionShapes.size(); j++)
//    {
//        btCollisionShape* shape = collisionShapes[j];
//        collisionShapes[j] = 0;
//        delete shape;
//    }
//
//    //delete dynamics world
//    delete dynamicsWorld;
//
//    //delete solver
//    delete solver;
//
//    //delete broadphase
//    delete overlappingPairCache;
//
//    //delete dispatcher
//    delete dispatcher;
//
//    delete collisionConfiguration;
//
//    //next line is optional: it will be cleared by the destructor when the array goes out of scope
//    collisionShapes.clear();
//
//    /////////

// Build the broadphase
    broadphase = new btDbvtBroadphase();

// Set up the collision configuration and dispatcher
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

// The actual physics solver
    solver = new btSequentialImpulseConstraintSolver;

// The world.
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-9.81f,0));
}

void PhysicsComponentSystem::destroy() {
    ComponentSystem::destroy();
}

void PhysicsComponentSystem::update(float deltaTime) {
    ComponentSystem::update(deltaTime);

//    dynamicsWorld->stepSimulation(deltaTime, 10);

    auto entityHandles = Application::getInstance().scene.registry.view<DeepsEngine::Component::PhysicsComponent>();
    for (auto entityHandle : entityHandles) {
        DeepsEngine::Entity entity = {entityHandle};
        auto &physicsComponent = entity.GetComponent<DeepsEngine::Component::PhysicsComponent>();
        auto &transformComponent = entity.GetComponent<DeepsEngine::Component::Transform>();

        if (physicsComponent.rigidBody) {
            btTransform trans;
            if (physicsComponent.rigidBody && physicsComponent.rigidBody->getMotionState())
            {
                physicsComponent.rigidBody->getMotionState()->getWorldTransform(trans);
                transformComponent.position = glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
//                transformComponent.rotation = glm::eulerAngles(glm::quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ()));
            }
        } else {
            auto quaternion = glm::quat(transformComponent.rotation);

            auto* motionState = new btDefaultMotionState(btTransform(
                    btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w).normalized(),
                    btVector3(transformComponent.position.x, transformComponent.position.y, transformComponent.position.z)
            ));

            btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                    physicsComponent.mass,
                    motionState,
                    physicsComponent.collisionShape
            );

            rigidBodyCI.m_friction = 0.0f;
            rigidBodyCI.m_restitution = 0.0f;
            rigidBodyCI.m_linearDamping = 0.0f;

            auto *rigidBody = new btRigidBody(rigidBodyCI);

//            rigidBody->setFlags(rigidBody->getFlags() | btCollisionObject::CollisionFlags::CF_DYNAMIC_OBJECT);

            rigidBody->setAngularFactor(0.0f);

            rigidBody->activate();
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
            dynamicsWorld->addRigidBody(rigidBody);
            physicsComponent.rigidBody = rigidBody;
        }
    }

    dynamicsWorld->stepSimulation(deltaTime, 10);
}