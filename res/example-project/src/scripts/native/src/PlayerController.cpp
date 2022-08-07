//
// Created by Deepak Ramalingam on 7/2/22.
//

#include "PlayerController.hpp"
#include "Component.h"
#include "Input.h"
#include "KeyCodes.h"
#include "DeepsMath.h"

void PlayerController::init() {
    NativeScript::init();

    this->speed = 10.0f;
    this->rotationSpeed = 5.0f;
    this->currentState = "Idle";

    auto& meshFilter = self.GetComponent<DeepsEngine::Component::MeshFilter>();
    runningAnimation = meshFilter.getAnimation("src/models/fox/fbx/running/fox-c00-no-facial-animations-running.fbx");
    idleAnimation = meshFilter.getAnimation("src/models/fox/fbx/wait-1/fox-c00-no-facial-animations-wait-1.fbx");
}

void PlayerController::update(double dt) {
    NativeScript::update(dt);

    auto& physicsComponent = self.GetComponent<DeepsEngine::Component::PhysicsComponent>();
    auto entityHandles = Application::getInstance().scene.registry.view<DeepsEngine::Component::Transform>();

    for(auto entityHandle : entityHandles) {
        DeepsEngine::Entity entity = {entityHandle};

        if (entity.HasComponent<DeepsEngine::Component::Tag>()) {
            if (entity.GetComponent<DeepsEngine::Component::Tag>().tag == "Main Camera") {
                // get camera entity front vector
                DeepsEngine::Component::Transform mainCameraTransformComponent = entity.GetComponent<DeepsEngine::Component::Transform>();
                glm::vec3 cameraFront = mainCameraTransformComponent.front();
                glm::vec3 cameraRight = mainCameraTransformComponent.right();
                auto& transform = self.GetComponent<DeepsEngine::Component::Transform>();

                // calculate running velocity vector
                glm::vec3 velocityDirection = glm::vec3(0.0f, 0.0f, 0.0f);

                // move player forward relative to camera
                if (Input::GetButtonDown(DeepsEngine::Key::Space)) {
                    btVector3 currentLinVel = physicsComponent.rigidBody->getLinearVelocity();

                    // TODO: jump
                    // TODO: jump
                    // TODO: jump
                    // TODO: jump
                    // TODO: jump
                    // TODO: jump
                    // TODO: jump

                    physicsComponent.rigidBody->setLinearVelocity(btVector3(currentLinVel.getX(), 5.0f, currentLinVel.getZ()));
                }

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

                if (glm::length2(velocityDirection) > 0.0f) {
                    glm::vec3 velocity = glm::normalize(velocityDirection) * this->speed;
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
