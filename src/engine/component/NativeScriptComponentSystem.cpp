//
// Created by Deepak Ramalingam on 6/11/22.
//

#include "NativeScriptComponentSystem.h"
#include "NativeScript.h"
#include "Logger.h"
#include "Application.h"
#include "Component.h"

#include <dlfcn.h>

#if defined(EMSCRIPTEN)

#include <emscripten.h>

EM_JS(void, doLoadLibrary, (), {
Asyncify.handleAsync(async() => {
try {
await loadDynamicLibrary('assets/project/src/scripts/native/web/libnative.wasm', { loadAsync: true, global: true, nodelete: true, fs: FS });
}
catch (error) {
console.log(error);
}
});
});

#endif

void NativeScriptComponentSystem::init() {
    ComponentSystem::init();

#if defined(EMSCRIPTEN)
    std::string libraryFolder = "web";
    std::string libraryFileName = "libnative.so";
#else
    std::string libraryFolder = "osx";
    std::string libraryFileName = "libnative.dylib";
#endif

#if defined(EMSCRIPTEN)
    doLoadLibrary();
#else
    std::string libraryPath = Application::getInstance().getProjectPath().append("src").append("scripts")
            .append("native").append(libraryFolder).append(libraryFileName);
    void* nativeScriptComponentLibrary = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!nativeScriptComponentLibrary) {
        Logger::Error("Cannot load library: " + std::string(dlerror()));
        exit(1);
    }
#endif
    dlerror();
}

void NativeScriptComponentSystem::destroy() {
    ComponentSystem::destroy();
    dlclose(RTLD_DEFAULT);
}

void NativeScriptComponentSystem::update(float deltaTime) {
    ComponentSystem::update(deltaTime);

    auto entityHandles = Application::getInstance().scene.registry.view<DeepsEngine::Component::NativeScriptComponent>();
    for (auto entityHandle : entityHandles) {
        DeepsEngine::Entity entity = {entityHandle};
        auto &nativeScriptComponent = entity.GetComponent<DeepsEngine::Component::NativeScriptComponent>();

        if (nativeScriptComponent.className.empty() || nativeScriptComponent.filePath.empty()) {
            continue;
        }

        if (nativeScriptComponent.shouldInit) {
            std::string createMethodName = "create_" + nativeScriptComponent.className;
            auto* createNativeScript = (create_t*) dlsym(RTLD_DEFAULT, createMethodName.c_str());
            const char* dlsym_error = dlerror();
            if (dlsym_error) {
                Logger::Error("Cannot load symbol create: " + std::string(dlsym_error));
                exit(1);
            }
            NativeScript* nativeScriptComponentInstance = createNativeScript(entity);
            nativeScriptComponent.nativeScript.reset(nativeScriptComponentInstance);
            nativeScriptComponent.nativeScript->init();
            nativeScriptComponent.shouldInit = false;
        } else if (nativeScriptComponent.nativeScript && nativeScriptComponent.shouldUpdate) {
            nativeScriptComponent.nativeScript->update(deltaTime);
        }
    }
}
