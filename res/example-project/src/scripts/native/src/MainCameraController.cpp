//
// Created by Deepak Ramalingam on 7/3/22.
//

#include "MainCameraController.hpp"
#include "Application.h"
#include "Component.h"
#include <glm/glm.hpp>

void MainCameraController::init() {
    NativeScript::init();

}

void MainCameraController::update(double dt) {
    NativeScript::init();

    auto entityHandles = Application::getInstance().scene.registry.view<DeepsEngine::Component::Transform>();

    for(auto entityHandle : entityHandles) {
        DeepsEngine::Entity entity = {entityHandle};

        if (entity.HasComponent<DeepsEngine::Component::Tag>()) {
            if (entity.GetComponent<DeepsEngine::Component::Tag>().tag == "Fox") {
                DeepsEngine::Component::Transform playerTransform = entity.GetComponent<DeepsEngine::Component::Transform>();
                Logger::Debug(std::to_string(playerTransform.position.x) + ", " + std::to_string(playerTransform.position.y) + ", " + std::to_string(playerTransform.position.z));
                self.GetComponent<DeepsEngine::Component::Transform>().position = playerTransform.position + glm::vec3(-4.0f, 1.0f, 0.0f);
            }
        }
    }
}
