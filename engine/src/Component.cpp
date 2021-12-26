//
// Created by Deepak Ramalingam on 12/25/21.
//

#include "Component.h"

std::string Component::getId() {
    return this->id;
}

void Component::setEntityId(std::string id) {
    this->id = id;
}

std::string Component::getEntityId() {
    return this->entityId;
}

void Component::setComponentSystemId(std::string componentSystemId) {
    this->componentSystemId = componentSystemId;
}

std::string Component::getComponentSystemId() {
    return this->componentSystemId;
}

std::string Component::getName() {
    return this->name;
}

void Component::setData(std::string data) {
    this->data = data;
}

std::string Component::getData() {
    return this->data;
}