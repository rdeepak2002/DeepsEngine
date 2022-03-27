#if defined(EMSCRIPTEN) or defined(DEVELOP_WEB)

#pragma once

#include<memory>

class game_impl;

class game {
    std::unique_ptr<game_impl> me;
public:
    game();
    ~game();
    void draw();
};

#endif