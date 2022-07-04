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

    radius = 8.0f;

    phi = 0.0f;
    phiSpeed = 1.0f;

    theta = -M_PI / 2;
    minTheta = 0.99 * -M_PI;
    maxTheta = 0.01f;
    thetaSpeed = 1.0f;
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

                // calculate angle to look at player wrt y-axis
                glm::vec3 vectorToPlayer = glm::normalize(playerTransform.position - transform.position);
                float angleToPlayer = glm::dot(glm::vec3(vectorToPlayer.x, 0.0f, vectorToPlayer.z), glm::vec3(transform.right().x, 0.0f, transform.right().z));
                transform.rotation.y += angleToPlayer;

                // move camera around player in spherical manner
                glm::vec3 offsetPosition = glm::vec3(radius * sin(theta) * cos(phi), radius * cos(theta), radius * sin(theta) * sin(phi));
                transform.position = playerTransform.position + offsetPosition;

                // update camera position variables based off user input
                if (Input::GetButtonDown(DeepsEngine::Key::Left)) {
                    phi += phiSpeed * float(dt);
                }

                if (Input::GetButtonDown(DeepsEngine::Key::Right)) {
                    phi -= phiSpeed * float(dt);
                }

                if (phi > 2 * M_PI) {
                    phi -= 2 * M_PI;
                }

                if (phi < -2 * M_PI) {
                    phi += 2 * M_PI;
                }

                if (Input::GetButtonDown(DeepsEngine::Key::Up)) {
                    theta += thetaSpeed * float(dt);
                }

                if (Input::GetButtonDown(DeepsEngine::Key::Down)) {
                    theta -= thetaSpeed * float(dt);
                }

                theta = max(theta, minTheta);
                theta = min(theta, maxTheta);
            }
        }
    }
}
