//
// Created by Deepak Ramalingam on 7/2/22.
//

#include "PlayerController.hpp"
#include "Component.h"
#include "Input.h"
#include "KeyCodes.h"

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
                }

                if (currentState != "Running") {
                    // TODO: uncomment this
//                    self.GetComponent<DeepsEngine::Component::MeshFilter>().setMeshPath("src/models/link_fbx/Dancing.fbx");
                    currentState = "Running";
                }
            }
        }
    }
}
