//
// Created by Deepak Ramalingam on 12/25/21.
//

#ifndef CORE_COMPONENT_H
#define CORE_COMPONENT_H

#include <string>

//template <typename T>

class Component {
private:
    std::string id;
    std::string entityId;
    std::string componentSystemId;
    std::string name;
    std::string data;
public:
    Component(std::string entityId, std::string name, std::string data);

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
