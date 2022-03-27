#if defined(EMSCRIPTEN) or defined(DEVELOP_WEB)

#pragma once

#include<memory>

class WebRendererImplementationExample;

class WebRenderer {
    std::unique_ptr<WebRendererImplementationExample> me;
public:
    WebRenderer();
    ~WebRenderer();
    void draw();
};

#endif