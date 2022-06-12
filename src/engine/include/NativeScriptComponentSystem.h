//
// Created by Deepak Ramalingam on 6/11/22.
//

#ifndef DEEPSENGINE_NATIVESCRIPTCOMPONENTSYSTEM_H
#define DEEPSENGINE_NATIVESCRIPTCOMPONENTSYSTEM_H


#include "ComponentSystem.h"

class NativeScriptComponentSystem : public ComponentSystem {
public:
    NativeScriptComponentSystem() = default;
    void init() override;
    void destroy() override;
    void update(float deltaTime) override;
};


#endif //DEEPSENGINE_NATIVESCRIPTCOMPONENTSYSTEM_H
