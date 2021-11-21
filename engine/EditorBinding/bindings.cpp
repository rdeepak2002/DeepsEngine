#include "bindings.h"
#include "../src/Renderer.h"

#include <thread>

Renderer *renderer;

std::string bindings::checkEngineStatus(int num) {
    return "Engine Running, received input " + std::to_string(num);
}

void bindings::createRenderer(bool showWindow, bool saveOutputRender) {
    if (renderer)
        renderer->shutDown();

    renderer = new Renderer(showWindow, saveOutputRender);

    renderer->init();
}

bool bindings::rendererShuttingDown() {
    return renderer->shuttingDown();
}

void bindings::updateRenderer() {
    renderer->render();
}

void bindings::shutDownRenderer() {
    renderer->shutDown();
}

Napi::String bindings::CheckEngineStatusWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    Napi::Number num = info[0].As<Napi::Number>();

    Napi::String returnValue = Napi::String::New(env, bindings::checkEngineStatus(num.Int64Value()));

    return returnValue;
}

void bindings::CreateRendererWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 2) {
        if (!info[0].IsBoolean()) {
            Napi::TypeError::New(env, "Boolean expected for show window").ThrowAsJavaScriptException();
        }

        if (!info[1].IsBoolean()) {
            Napi::TypeError::New(env, "Boolean expected for save output render").ThrowAsJavaScriptException();
        }
    }

    Napi::Boolean showWindow = info[0].As<Napi::Boolean>();
    Napi::Boolean saveOutputRender = info[1].As<Napi::Boolean>();

    bindings::createRenderer(showWindow.Value(), saveOutputRender.Value());
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
