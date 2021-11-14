#include "functionexample.h"
#include "Renderer.h"

#include <thread>


std::string functionexample::hello(int num) {
    return "Hello World " + std::to_string(num);
}


int threadFunc(Renderer* renderer) {
//    Renderer* renderer;
//    renderer = new Renderer();
//
//    renderer->init();

    while(!renderer->shuttingDown()) {
//        // TODO: call pollEvents() on main thread
//        renderer->pollEvents();

//        printf("calling render\n");
        renderer->render();
    }

    printf("render shut down\n");

    return 0;
}

void functionexample::startRenderer() {
    Renderer* renderer;
    renderer = new Renderer();

    renderer->init();

    std::thread th3(threadFunc, renderer);
    th3.detach();

    while(!renderer->shuttingDown()) {
        // call pollEvents() on main thread
        // TODO: use this guide to call poll events async on main thread https://stackoverflow.com/questions/17354260/c-stdasync-run-on-main-thread
        renderer->pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

//    threadFunc(renderer);
}

Napi::String functionexample::HelloWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Numberexpected").ThrowAsJavaScriptException();
    }
    Napi::Number num = info[0].As<Napi::Number>();

    Napi::String returnValue = Napi::String::New(env, functionexample::hello(num.Int64Value()));

    return returnValue;
}

void functionexample::StartRendererWrapped(const Napi::CallbackInfo &info) {
    functionexample::startRenderer();
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
            "hello", Napi::Function::New(env, functionexample::HelloWrapped)
    );

    exports.Set(
            "startRenderer", Napi::Function::New(env, functionexample::StartRendererWrapped)
    );

    return exports;
}
