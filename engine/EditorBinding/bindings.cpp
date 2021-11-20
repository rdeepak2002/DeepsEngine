#include "bindings.h"
#include "../src/Renderer.h"

#include <thread>

Renderer* renderer;

std::string bindings::checkEngineStatus(int num) {
    return "Engine Running, received input " + std::to_string(num);
}

void bindings::createRenderer() {
    if(renderer)
        renderer->shutDown();

    renderer = new Renderer();

    renderer->init();
}

bool bindings::rendererShuttingDown() {
    return renderer->shuttingDown();
}

void bindings::updateRenderer() {
    renderer->pollEvents();
    renderer->render();
}

void bindings::shutDownRenderer() {
    renderer->shutDown();
}

Napi::String bindings::CheckEngineStatusWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Numberexpected").ThrowAsJavaScriptException();
    }
    Napi::Number num = info[0].As<Napi::Number>();

    Napi::String returnValue = Napi::String::New(env, bindings::checkEngineStatus(num.Int64Value()));

    return returnValue;
}

void bindings::CreateRendererWrapped(const Napi::CallbackInfo &info) {
    bindings::createRenderer();
}

void bindings::UpdateRendererWrapped(const Napi::CallbackInfo &info) {
    bindings::updateRenderer();
}

void bindings::ShutDownRendererWrapped(const Napi::CallbackInfo &info) {
    bindings::shutDownRenderer();
}

Napi::Boolean bindings::RendererShuttingDownWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Boolean returnValue = Napi::Boolean::New(env, bindings::rendererShuttingDown());

    return returnValue;
}

Napi::Object bindings::Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
            "checkEngineStatus", Napi::Function::New(env, bindings::CheckEngineStatusWrapped)
    );

    exports.Set(
            "createRenderer", Napi::Function::New(env, bindings::CreateRendererWrapped)
    );

    exports.Set(
            "updateRenderer", Napi::Function::New(env, bindings::UpdateRendererWrapped)
    );

    exports.Set(
            "rendererShuttingDown", Napi::Function::New(env, bindings::RendererShuttingDownWrapped)
    );

    exports.Set(
            "shutDownRenderer", Napi::Function::New(env, bindings::ShutDownRendererWrapped)
    );

    return exports;
}
