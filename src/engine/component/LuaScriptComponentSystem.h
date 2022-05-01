//
// Created by Deepak Ramalingam on 5/1/22.
//

#ifndef EDITOR_LUASCRIPTCOMPONENTSYSTEM_H
#define EDITOR_LUASCRIPTCOMPONENTSYSTEM_H

#define SOL_ALL_SAFETIES_ON 1
#include "src/engine/include/sol.hpp"

class LuaScriptComponentSystem {
public:
    LuaScriptComponentSystem() {}
    void init();
    void update(float deltaTime);
private:
    sol::state lua;
};


#endif //EDITOR_LUASCRIPTCOMPONENTSYSTEM_H
