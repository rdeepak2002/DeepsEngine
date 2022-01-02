//
// Created by Deepak Ramalingam on 12/25/21.
//

#include "ComponentSystem.h"

std::string ComponentSystem::getId() {
    return this->id;
}

std::string ComponentSystem::getName() {
    return this->name;
}

void ComponentSystem::addComponent(Component *component) {
    if (component)
        components.insert(std::pair<std::string, Component *>(component->getId(), component));
}

void ComponentSystem::removeComponent(Component *component) {
    if (component)
        components.erase(component->getId());
}