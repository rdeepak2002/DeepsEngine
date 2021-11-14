#include "functionexample.h"
#include "Renderer.h"

std::string functionexample::hello(int num) {
    return "Hello World " + std::to_string(num);
}

void functionexample::startRenderer() {
    Renderer renderer;
    renderer.startOpenGL();
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
