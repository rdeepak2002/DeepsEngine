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

    radius = 12.0f;

    phi = 0.0f;
    phiSpeed = 0.2f;

    theta = -M_PI / 4;
    minTheta = -0.95 * M_PI;
    maxTheta = -0.05f;
    thetaSpeed = 0.2f;

    oldMousePosition = {0.0f, 0.0f};

    firstMouse = false;

    Logger::Debug("Init MainCameraController");
}

void MainCameraController::update(double dt) {
    NativeScript::init();

    glm::vec2 dMousePos = Input::GetMouseMovement();

    auto entityHandles = Application::getInstance().scene.registry.view<DeepsEngine::Component::Transform>();
    bool foundTarget = false;

    for(auto entityHandle : entityHandles) {
        DeepsEngine::Entity entity = {entityHandle};

        if (entity.HasComponent<DeepsEngine::Component::Tag>()) {
            if (entity.GetComponent<DeepsEngine::Component::Tag>().tag == "Samus") {
                foundTarget = true;
                auto& playerTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
                auto& transform = self.GetComponent<DeepsEngine::Component::Transform>();

                // calculate angle to look at player wrt y-axis
                transform.rotation.y = phi;
                transform.rotation.x = abs(theta) - M_PI / 2;

                // move camera around player in spherical manner
                glm::vec3 offsetPosition = glm::vec3(radius * sin(theta) * cos(phi), radius * cos(theta), radius * sin(theta) * sin(phi));
                glm::vec3 cameraTargetOffset = glm::vec3(0, 0.8, 0);
                transform.position = playerTransform.position + cameraTargetOffset + offsetPosition;

                // update camera position variables based off user input
                phi += phiSpeed * float(dt) * dMousePos.x;

                if (phi > 2 * M_PI) {
                    phi -= 2 * M_PI;
                }

                if (phi < -2 * M_PI) {
                    phi += 2 * M_PI;
                }

                theta += thetaSpeed * float(dt) * dMousePos.y;

                theta = max(theta, minTheta);
                theta = min(theta, maxTheta);
            }
        }
    }
    
    if (!foundTarget) {
        Logger::Warn("MainCameraController cannot find target");
    }
}
