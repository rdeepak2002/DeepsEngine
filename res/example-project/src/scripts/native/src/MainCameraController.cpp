//
// Created by Deepak Ramalingam on 7/3/22.
//

#include <glm/glm.hpp>
#include "MainCameraController.hpp"
#include "Application.h"
#include "Component.h"
#include "Input.h"
#include "KeyCodes.h"

void MainCameraController::init() {
    NativeScript::init();

    rotateSpeed = 1.0f;
    radius = 8.0f;
    angle = 0.0f;
    angleVel = 1.0f;

//    auto& transform = self.GetComponent<DeepsEngine::Component::Transform>();
//    transform.rotation.y = 3.14f;
//    transform.position.x = 15.0f;
}

void MainCameraController::update(double dt) {
    NativeScript::init();

    auto entityHandles = Application::getInstance().scene.registry.view<DeepsEngine::Component::Transform>();

    for(auto entityHandle : entityHandles) {
        DeepsEngine::Entity entity = {entityHandle};

        if (entity.HasComponent<DeepsEngine::Component::Tag>()) {
            if (entity.GetComponent<DeepsEngine::Component::Tag>().tag == "Fox") {
                auto& playerTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
                auto& transform = self.GetComponent<DeepsEngine::Component::Transform>();

                // calculate angle to look at player
                glm::vec3 vectorToPlayer = glm::normalize(playerTransform.position - transform.position);
                vectorToPlayer.y = 0;
                glm::vec3 firstVec = transform.right();
                firstVec.y = 0;
                float angleToPlayer = glm::dot(firstVec, vectorToPlayer);
                transform.rotation.y += angleToPlayer;

                // offset of camera from player
                glm::vec3 offsetPosition = glm::vec3(sin(angle) * radius, 1.0f, cos(angle) * radius);
                glm::vec3 targetPosition = playerTransform.position + offsetPosition;

                transform.position = targetPosition;

                // turn camera around player
                if (Input::GetButtonDown(DeepsEngine::Key::Right)) {
                    angle += angleVel * float(dt);
                }

                if (Input::GetButtonDown(DeepsEngine::Key::Left)) {
                    angle -= angleVel * float(dt);
                }
            }
        }
    }
}
