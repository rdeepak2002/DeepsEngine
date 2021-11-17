#include "functionexample.h"
#include "Renderer.h"

#include <thread>

Renderer* renderer;


std::string functionexample::hello(int num) {
    return "Hello World " + std::to_string(num);
}


int threadFunc(Renderer* renderer) {
//    Renderer* renderer;
//    renderer = new Renderer();
//
//    renderer->init();

//    while(!renderer->shuttingDown()) {
//        // TODO: call pollEvents() on main thread
//        renderer->pollEvents();

//        printf("calling render\n");
        renderer->render();
//    }

    printf("render shut down\n");

    return 0;
}

void functionexample::createRenderer() {
    renderer = new Renderer();

    renderer->init();

//    std::thread th3(threadFunc, renderer);
//    th3.detach();
//
//    while(!renderer->shuttingDown()) {
//        // call pollEvents() on main thread
//        // TODO: use this guide to call poll events async on main thread https://stackoverflow.com/questions/17354260/c-stdasync-run-on-main-thread
//        renderer->pollEvents();
//        std::this_thread::sleep_for(std::chrono::milliseconds(16));
//    }

//    threadFunc(renderer);
}

bool functionexample::rendererShuttingDown() {
    return renderer->shuttingDown();
}

void functionexample::updateRenderer() {
    if(!renderer->shuttingDown()) {
        renderer->pollEvents();
        renderer->render();
    }
    else {
        renderer->shutDown();
    }
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

void functionexample::CreateRendererWrapped(const Napi::CallbackInfo &info) {
    functionexample::createRenderer();
}

void functionexample::UpdateRendererWrapped(const Napi::CallbackInfo &info) {
    functionexample::updateRenderer();
}

Napi::Boolean functionexample::RendererShuttingDownWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Boolean returnValue = Napi::Boolean::New(env, functionexample::rendererShuttingDown());

    return returnValue;
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
            "hello", Napi::Function::New(env, functionexample::HelloWrapped)
    );

    exports.Set(
            "createRenderer", Napi::Function::New(env, functionexample::CreateRendererWrapped)
    );

    exports.Set(
            "updateRenderer", Napi::Function::New(env, functionexample::UpdateRendererWrapped)
    );

    exports.Set(
            "rendererShuttingDown", Napi::Function::New(env, functionexample::RendererShuttingDownWrapped)
    );

    return exports;
}
