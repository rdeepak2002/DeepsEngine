//
// Created by Deepak Ramalingam on 12/25/21.
//

#ifndef CORE_COMPONENT_H
#define CORE_COMPONENT_H

#include <string>
//#include "uuid.h"

//template <typename T>

class Component {
private:
    std::string id;
    std::string entityId;
    std::string componentSystemId;
    std::string name;
    std::string data;
public:
    Component(std::string entityId, std::string name, std::string data) {
        this->entityId = entityId;
        this->name = name;
        this->data = data;
//        id = uuid::generate_uuid_v4();
        // TODO: generate uuid for component
        id = "some_unique_component_id";
        componentSystemId = "unknown_component_system_id";
    }

    std::string getId();
    void setEntityId(std::string id);
    std::string getEntityId();
    void setComponentSystemId(std::string id);
    std::string getComponentSystemId();
    std::string getName();
    void setData(std::string data);
    std::string getData();
};


#endif //CORE_COMPONENT_H
