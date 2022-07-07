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

    this->speed = 5.0f;
    this->currentState = "Idle";
}

void PlayerController::update(double dt) {
    NativeScript::update(dt);

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
                    transform.position += velocity * float(dt);

                    // rotate character in direction of movement
                    glm::vec3 startPos = glm::vec3(transform.position.x, 0.0f, transform.position.z);
                    glm::vec3 lookAtPos = glm::vec3(velocityDirection.x, 0.0f, velocityDirection.z);
                    glm::quat q = DeepsMath::safeQuatLookAt(startPos, startPos - lookAtPos, transform.up(), transform.up());
                    glm::vec3 vec = glm::eulerAngles(q);
                    transform.rotation = vec;
                }

                // set animation based off state
                bool moving = glm::length2(velocityDirection) == 0;

                if (moving) {
                    if (currentState != "Idle") {
                        self.GetComponent<DeepsEngine::Component::MeshFilter>().setMeshPath("src/models/fox/animation/idle/Idle.dae");
                        currentState = "Idle";
                    }
                } else {
                    if (currentState != "Running") {
                        self.GetComponent<DeepsEngine::Component::MeshFilter>().setMeshPath("src/models/fox/animation/running/Running.dae");
                        currentState = "Running";
                    }
                }
            }
        }
    }
}
