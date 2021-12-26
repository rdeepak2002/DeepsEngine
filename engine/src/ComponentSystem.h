//
// Created by Deepak Ramalingam on 12/25/21.
//

#ifndef CORE_COMPONENTSYSTEM_H
#define CORE_COMPONENTSYSTEM_H


#include <map>
#include "Component.h"

class ComponentSystem {
private:
    std::string id;
    std::string name;
public:
    std::string getId();
    std::string getName();
    std::map<std::string, Component*> components;        // map of {componentId: componentObj}
    ComponentSystem(std::string name) {
        // TODO: generate guid
        id = "some_unique_component_system_id";
        this->name = name;
    }
    void addComponent(Component* component);
    void removeComponent(Component* component);
};


#endif //CORE_COMPONENTSYSTEM_H
