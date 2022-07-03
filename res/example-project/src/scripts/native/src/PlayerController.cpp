//
// Created by Deepak Ramalingam on 7/2/22.
//

#include "PlayerController.hpp"
#include "Component.h"
#include "Input.h"
#include "KeyCodes.h"

void PlayerController::init() {
    NativeScript::init();

    this->speed = 0.1f;
}

void PlayerController::update(double dt) {
    NativeScript::update(dt);

    // get camera entity front vector
    std::vector<DeepsEngine::Entity> cameraEntities = Application::getInstance().scene.GetCameraEntities();
    std::unique_ptr<DeepsEngine::Entity> mainCameraEntity = std::make_unique<DeepsEngine::Entity>(cameraEntities.front());
    DeepsEngine::Component::Transform mainCameraTransformComponent = mainCameraEntity->GetComponent<DeepsEngine::Component::Transform>();
    glm::vec3 cameraFront = mainCameraTransformComponent.front();
    glm::vec3 cameraRight = mainCameraTransformComponent.right();

    // calculate running velocity vector
    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    // move player forward relative to camera
    if (Input::GetButtonDown(DeepsEngine::Key::W)) {
        velocity += cameraFront * speed;
    }

    if (Input::GetButtonDown(DeepsEngine::Key::S)) {
        velocity -= cameraFront * speed;
    }

    if (Input::GetButtonDown(DeepsEngine::Key::D)) {
        velocity += cameraRight * speed;
    }

    if (Input::GetButtonDown(DeepsEngine::Key::A)) {
        velocity -= cameraRight * speed;
    }

    velocity.y = 0.0f;

    self.GetComponent<DeepsEngine::Component::Transform>().position += velocity;
}
