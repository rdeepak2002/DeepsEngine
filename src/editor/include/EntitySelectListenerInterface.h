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
#include <QHash>
#include <QTreeWidgetItem>
#include "Entity.h"

class EntitySelectListenerInterface
{
public:
    virtual void onEntitySelected(QHash<QTreeWidgetItem*, std::shared_ptr<DeepsEngine::Entity>> *entityItemMap, QTreeWidgetItem* listItem) {
        Logger::Error("onEntitySelected() not implemented");
        exit(1);
    }
};

#endif //EDITOR_ENTITYSELECTLISTENERINTERFACE_H

#endif //DEEPSENGINE_ENTITYSELECTLISTENERINTERFACE_H
