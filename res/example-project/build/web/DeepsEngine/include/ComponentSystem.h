//
// Created by Deepak Ramalingam on 5/1/22.
//

#ifndef EDITOR_COMPONENTSYSTEM_H
#define EDITOR_COMPONENTSYSTEM_H

#include <iostream>

class ComponentSystem
{
public:
    virtual void init () {};
    virtual void update (float dt) {};
};

#endif //EDITOR_COMPONENTSYSTEM_H
