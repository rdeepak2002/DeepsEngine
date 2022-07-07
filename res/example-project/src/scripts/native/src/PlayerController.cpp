//
// Created by Deepak Ramalingam on 7/2/22.
//

#include "PlayerController.hpp"
#include "Component.h"
#include "Input.h"
#include "KeyCodes.h"
#include <glm/ext.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/matrix_decompose.hpp>

void PlayerController::init() {
    NativeScript::init();

    this->speed = 5.0f;
    this->currentState = "Idle";
}

glm::quat safeQuatLookAt(
        glm::vec3 const& lookFrom,
        glm::vec3 const& lookTo,
        glm::vec3 const& up,
        glm::vec3 const& alternativeUp)
{
    glm::vec3  direction       = lookTo - lookFrom;
    float      directionLength = glm::length(direction);

    // Check if the direction is valid; Also deals with NaN
    if(!(directionLength > 0.0001))
        return glm::quat(1, 0, 0, 0); // Just return identity

    // Normalize direction
    direction /= directionLength;

    // Is the normal up (nearly) parallel to direction?
    if(glm::abs(glm::dot(direction, up)) > .9999f) {
        // Use alternative up
        return glm::quatLookAt(direction, alternativeUp);
    }
    else {
        return glm::quatLookAt(direction, up);
    }
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
                    glm::quat q = safeQuatLookAt(transform.position, transform.position - velocityDirection, glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
                    glm::vec3 vec = glm::eulerAngles(q);
                    transform.rotation = vec;
                    Logger::Debug(glm::to_string(vec));
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
