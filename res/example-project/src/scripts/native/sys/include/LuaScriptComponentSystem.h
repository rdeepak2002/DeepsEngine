//
// Created by Deepak Ramalingam on 5/1/22.
//

#ifndef EDITOR_LUASCRIPTCOMPONENTSYSTEM_H
#define EDITOR_LUASCRIPTCOMPONENTSYSTEM_H

#define SOL_ALL_SAFETIES_ON 1
#include "ComponentSystem.h"

#define SOL_ALL_SAFETIES_ON 1
#include "sol/state.hpp"

class LuaScriptComponentSystem : public ComponentSystem {
public:
    LuaScriptComponentSystem() = default;
    void init() override;
    void destroy() override;
    void update(float deltaTime) override;
private:
    sol::state lua;
};


#endif //EDITOR_LUASCRIPTCOMPONENTSYSTEM_H
