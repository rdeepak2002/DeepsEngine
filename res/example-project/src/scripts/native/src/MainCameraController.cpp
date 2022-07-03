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

    radius = 5.0f;
    angle = 0.0f;
    angleVel = 1.0f;
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

                // offset of camera from player
                glm::vec3 offsetPosition = glm::vec3(sin(angle) * radius, 1.0f, cos(angle) * radius);

                // turn camera around player
                if (Input::GetButtonDown(DeepsEngine::Key::Right)) {
                    angle += dt * angleVel;
                }

                if (Input::GetButtonDown(DeepsEngine::Key::Left)) {
                    angle -= dt * angleVel;
                }

                // calculate angle to look at player
                glm::vec3 vectorToPlayer = glm::normalize(playerTransform.position - transform.position);
                vectorToPlayer.y = 0;
                float angleToPlayer = glm::dot(transform.right(), vectorToPlayer);

                transform.position = playerTransform.position + offsetPosition;
                transform.rotation.y += angleToPlayer;
            }
        }
    }
}
