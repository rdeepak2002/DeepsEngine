#if defined(EMSCRIPTEN) or defined(DEVELOP_WEB)

#pragma once

#include<memory>

class game_impl;

class WebRenderer {
    std::unique_ptr<game_impl> me;
public:
    WebRenderer();
    ~WebRenderer();
    void draw();
};

#endif