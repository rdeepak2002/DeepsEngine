#include <napi.h>

namespace bindings {
    std::string checkEngineStatus(int num);

    void createRenderer(bool showWindow, bool saveOutputRender, std::string projectPath);

    void updateRenderer();

    bool rendererShuttingDown();

    void shutDownRenderer();

    std::string getCachedFrame();

    void handleEditorResize(int width, int height);

    Napi::String GetCachedFrameWrapped(const Napi::CallbackInfo &info);

    Napi::String CheckEngineStatusWrapped(const Napi::CallbackInfo &info);

    void CreateRendererWrapped(const Napi::CallbackInfo &info);

    void UpdateRendererWrapped(const Napi::CallbackInfo &info);

    void ShutDownRendererWrapped(const Napi::CallbackInfo &info);

    void HandleEditorResizeWrapped(const Napi::CallbackInfo &info);

    Napi::Boolean RendererShuttingDownWrapped(const Napi::CallbackInfo &info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
}
