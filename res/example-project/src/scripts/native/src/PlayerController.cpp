//
// Created by Deepak Ramalingam on 7/2/22.
//

#include "PlayerController.hpp"
#include "Component.h"
#include "Input.h"
#include "KeyCodes.h"
#include "DeepsMath.h"
#include "Application.h"
#include "PhysicsComponentSystem.h"

void PlayerController::init() {
    NativeScript::init();

    Logger::Debug("Init PlayerController");

    auto& meshFilter = self.GetComponent<DeepsEngine::Component::MeshFilter>();
    runningAnimation = meshFilter.getAnimation("src/models/samus/motion/body/c00/run/samus-c00-combined-run.fbx");
    idleAnimation = meshFilter.getAnimation("src/models/samus/motion/body/c00/wait-1/samus-c00-combined-wait-1.fbx");
}

void PlayerController::update(double dt) {
    NativeScript::update(dt);

    auto& transform = self.GetComponent<DeepsEngine::Component::Transform>();
    auto& physicsComponent = self.GetComponent<DeepsEngine::Component::PhysicsComponent>();
    auto entityHandles = Application::getInstance().scene.registry.view<DeepsEngine::Component::Transform>();

    for(auto entityHandle : entityHandles) {
        DeepsEngine::Entity entity = {entityHandle};

        if (entity.HasComponent<DeepsEngine::Component::Tag>()) {
            if (entity.GetComponent<DeepsEngine::Component::Tag>().tag == "Main Camera") {
                // check if grounded
                btTransform btTrans = physicsComponent.rigidBody->getWorldTransform();
                btVector3 btFrom(btTrans.getOrigin().getX(), btTrans.getOrigin().getY() + 0.02f, btTrans.getOrigin().getZ());
                btVector3 btTo(btTrans.getOrigin().getX(), -5, btTrans.getOrigin().getZ());
                btCollisionWorld::ClosestRayResultCallback groundRaycastResult(btFrom, btTo);
                ComponentSystem* componentSystem = Application::getInstance().componentSystems["PhysicsComponentSystem"];
                auto* physicsComponentSystem = dynamic_cast<PhysicsComponentSystem*>(componentSystem);
                physicsComponentSystem->dynamicsWorld->rayTest(btFrom, btTo, groundRaycastResult); // m_btWorld is btDiscreteDynamicsWorld
                bool grounded = false;

                if (groundRaycastResult.hasHit()) {
                    btVector3 hitPoint = groundRaycastResult.m_hitPointWorld;
                    glm::vec3 hitPointGlm = glm::vec3(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ());
                    glm::vec3 btFromGlm = glm::vec3(btFrom.getX(), btFrom.getY(), btFrom.getZ());
                    float distanceToGround = glm::distance(hitPointGlm, btFromGlm);
                    if (distanceToGround < 0.02) {
                        grounded = true;
                    }
                } else {
                    grounded = false;
                }

                // allow player to jump
                if (Input::GetButtonDown(DeepsEngine::Key::Space)) {
                    if (grounded) {
                        btVector3 currentLinVel = physicsComponent.rigidBody->getLinearVelocity();
                        physicsComponent.rigidBody->setLinearVelocity(btVector3(currentLinVel.getX() * jumpSpeedReductionFactor, jumpSpeed, currentLinVel.getZ() * jumpSpeedReductionFactor));
                        grounded = false;
                    }
                }

                // get camera entity front vector
                DeepsEngine::Component::Transform mainCameraTransformComponent = entity.GetComponent<DeepsEngine::Component::Transform>();
                glm::vec3 cameraFront = mainCameraTransformComponent.front();
                glm::vec3 cameraRight = mainCameraTransformComponent.right();

                // calculate running velocity vector
                glm::vec3 velocityDirection = glm::vec3(0.0f, 0.0f, 0.0f);

                // move player forward relative to camera
                if (Input::GetButtonDown(DeepsEngine::Key::W)) {
                    velocityDirection += cameraFront;
                }

                if (Input::GetButtonDown(DeepsEngine::Key::S)) {
                    velocityDirection -= cameraFront;
                }

                if (Input::GetButtonDown(DeepsEngine::Key::D)) {
                    velocityDirection += cameraRight;
                }

                if (Input::GetButtonDown(DeepsEngine::Key::A)) {
                    velocityDirection -= cameraRight;
                }

                velocityDirection.y = 0.0f;
                velocityDirection = glm::normalize(velocityDirection);

                if (glm::length2(velocityDirection) > 0.0f) {
                    glm::vec3 velocity = velocityDirection * this->speed;
                    if (!grounded) {
                        velocity.x *= jumpSpeedReductionFactor;
                        velocity.z *= jumpSpeedReductionFactor;
                    }
                    btVector3 currentLinVel = physicsComponent.rigidBody->getLinearVelocity();
                    physicsComponent.rigidBody->setLinearVelocity(btVector3(velocity.x, currentLinVel.getY(), velocity.z));

                    // rotate character in direction of movement
                    glm::vec3 startPos = glm::vec3(transform.position.x, 0.0f, transform.position.z);
                    glm::vec3 lookAtPos = glm::vec3(velocityDirection.x, 0.0f, velocityDirection.z);
                    glm::quat targetRotationQuat = DeepsMath::safeQuatLookAt(startPos, startPos - lookAtPos, transform.up(), transform.up());
                    glm::vec3 targetRotationEulerAngles = glm::eulerAngles(targetRotationQuat);
                    physicsComponent.rigidBody->getWorldTransform().setRotation(btQuaternion(targetRotationQuat.x, targetRotationQuat.y, targetRotationQuat.z, targetRotationQuat.w));
                }

                // set animation based off state
                bool moving = glm::length2(velocityDirection) > 0.0001f;

                if (moving) {
                    if (currentState != "Running") {
                        self.GetComponent<DeepsEngine::Component::MeshFilter>().playAnimation(runningAnimation);
                        currentState = "Running";
                    }
                } else {
                    if (currentState != "Idle") {
                        self.GetComponent<DeepsEngine::Component::MeshFilter>().playAnimation(idleAnimation);
                        currentState = "Idle";
                    }
                }
            }
        }
    }
}
