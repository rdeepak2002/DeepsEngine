//
// Created by Deepak Ramalingam on 12/30/21.
//

#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include <iostream>
#include <set>
#include "ECS.h"

class System
{
public:
    std::set<Entity> mEntities;
};


#endif //CORE_SYSTEM_H
