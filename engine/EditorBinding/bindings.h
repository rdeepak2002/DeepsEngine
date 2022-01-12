#include <napi.h>

namespace bindings {
    std::string checkEngineStatus(int num);

    void createRenderer(bool showWindow, bool saveOutputRender, std::string projectPath);

    void updateRenderer();

    bool rendererShuttingDown();

    void shutDownRenderer();

    void startPlayMode();

    std::string getCachedFrame();

    void handleEditorResize(int width, int height);

    void addEntity(std::string name);

    void updateComponent(std::uint32_t entity, std::string json);

    int getNumEntities();

    int* getEntities(int entitiesArr[]);

    void handleEditorDragging(float dx, float dy);

    Napi::String GetCachedFrameWrapped(const Napi::CallbackInfo &info);

    Napi::String CheckEngineStatusWrapped(const Napi::CallbackInfo &info);

    void CreateRendererWrapped(const Napi::CallbackInfo &info);

    void UpdateRendererWrapped(const Napi::CallbackInfo &info);

    void ShutDownRendererWrapped(const Napi::CallbackInfo &info);

    void HandleEditorResizeWrapped(const Napi::CallbackInfo &info);

    void StartPlayModeWrapped(const Napi::CallbackInfo &info);

    Napi::Boolean RendererShuttingDownWrapped(const Napi::CallbackInfo &info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);

    void AddEntityWrapped(const Napi::CallbackInfo &info);

    Napi::Uint8Array GetEntitiesWrapped(const Napi::CallbackInfo &info);

    void UpdateComponentWrapped(const Napi::CallbackInfo &info);

    void HandleEditorDraggingWrapped(const Napi::CallbackInfo &info);
}
