//
// Created by Deepak Ramalingam on 6/11/22.
//

#include "NativeScriptComponentSystem.h"
#include "NativeScript.h"
#include "Logger.h"
#include "Application.h"

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

    create_t* createNativeScript = (create_t*) dlsym(RTLD_DEFAULT, "create_SpinningEntity");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        Logger::Error("Cannot load symbol create: " + std::string(dlsym_error));
        exit(1);
    }

    destroy_t* destroyNativeScript = (destroy_t*) dlsym(RTLD_DEFAULT, "destroy_SpinningEntity");
    dlsym_error = dlerror();
    if (dlsym_error) {
        Logger::Error("Cannot load symbol destroy: " + std::string(dlsym_error));
        exit(1);
    }

    NativeScript* nativeScriptComponentInstance = createNativeScript();
    nativeScriptComponentInstance->init();
    nativeScriptComponentInstance->update(1.0);
    destroyNativeScript(nativeScriptComponentInstance);
}

void NativeScriptComponentSystem::destroy() {
    ComponentSystem::destroy();
    dlclose(RTLD_DEFAULT);
}

void NativeScriptComponentSystem::update(float deltaTime) {
    ComponentSystem::update(deltaTime);
}
