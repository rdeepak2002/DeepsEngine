#include <napi.h>

namespace functionexample {
    std::string hello(int num);

    void createRenderer();
    void updateRenderer();
    bool rendererShuttingDown();
    void shutDownRenderer();

    Napi::String HelloWrapped(const Napi::CallbackInfo &info);

    void CreateRendererWrapped(const Napi::CallbackInfo &info);

    void UpdateRendererWrapped(const Napi::CallbackInfo &info);

    void ShutDownRendererWrapped(const Napi::CallbackInfo &info);

    Napi::Boolean RendererShuttingDownWrapped(const Napi::CallbackInfo &info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
}