//
// Created by Deepak Ramalingam on 5/5/22.
//

#ifndef DEEPSENGINE_ENTITYSELECTLISTENERINTERFACE_H
#define DEEPSENGINE_ENTITYSELECTLISTENERINTERFACE_H

//
// Created by Deepak Ramalingam on 4/30/22.
//

#ifndef EDITOR_ENTITYSELECTLISTENERINTERFACE_H
#define EDITOR_ENTITYSELECTLISTENERINTERFACE_H

//#pragma once

#include <iostream>
#include <QListWidgetItem>
#include "Entity.h"

class EntitySelectListenerInterface
{
public:
    virtual void onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem) {
        std::cout << "onEntitySelected() not implemented" << std::endl;
        exit(1);
    }
};

#endif //EDITOR_ENTITYSELECTLISTENERINTERFACE_H

#endif //DEEPSENGINE_ENTITYSELECTLISTENERINTERFACE_H
