//
// Created by Deepak Ramalingam on 5/12/22.
//

#ifndef DEEPSENGINE_COMPONENTWIDGET_H
#define DEEPSENGINE_COMPONENTWIDGET_H

#include "Component.h"
#include "Logger.h"

class ComponentWidget: public QWidget {
public:
    virtual void setComponent(DeepsEngine::Component::Component* component) {
        Logger::Error("Not implemented");
        exit(1);
    }
    virtual std::string getName() {
        Logger::Error("Not implemented");
        exit(1);
    }
};

#endif //DEEPSENGINE_COMPONENTWIDGET_H
