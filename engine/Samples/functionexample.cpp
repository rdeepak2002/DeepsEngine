#include "functionexample.h"
#include "Renderer.h"

#include <thread>

Renderer* renderer;

std::string functionexample::hello(int num) {
    return "Hello World " + std::to_string(num);
}

void functionexample::createRenderer() {
    renderer = new Renderer();

    renderer->init();
}

bool functionexample::rendererShuttingDown() {
    return renderer->shuttingDown();
}

void functionexample::updateRenderer() {
    renderer->pollEvents();
    renderer->render();
}

void functionexample::shutDownRenderer() {
    renderer->shutDown();
//    delete renderer;
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

void functionexample::ShutDownRendererWrapped(const Napi::CallbackInfo &info) {
    functionexample::shutDownRenderer();
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

    exports.Set(
            "shutDownRenderer", Napi::Function::New(env, functionexample::ShutDownRendererWrapped)
    );

    return exports;
}
