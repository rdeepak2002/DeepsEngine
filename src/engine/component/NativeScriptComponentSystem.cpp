//
// Created by Deepak Ramalingam on 6/11/22.
//

#include "NativeScriptComponentSystem.h"
#include "NativeScriptComponent.h"
#include "Logger.h"

#include <dlfcn.h>

void NativeScriptComponentSystem::init() {
    ComponentSystem::init();

    void* nativeScriptComponentLibrary = dlopen("/Users/deepakramalingam/Desktop/native/cmake-build-debug/libnative.dylib", RTLD_LAZY);
    if (!nativeScriptComponentLibrary) {
        Logger::Error("Cannot load library: " + std::string(dlerror()));
        exit(1);
    }

    dlerror();

    create_t* createNativeScriptComponent = (create_t*) dlsym(nativeScriptComponentLibrary, "create_SpinningEntity");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        Logger::Error("Cannot load symbol create: " + std::string(dlsym_error));
        exit(1);
    }

    destroy_t* destroyNativeScriptComponent = (destroy_t*) dlsym(nativeScriptComponentLibrary, "destroy_SpinningEntity");
    dlsym_error = dlerror();
    if (dlsym_error) {
        Logger::Error("Cannot load symbol destroy: " + std::string(dlsym_error));
        exit(1);
    }

    NativeScriptComponent* nativeScriptComponentInstance = createNativeScriptComponent();
    nativeScriptComponentInstance->init();
    destroyNativeScriptComponent(nativeScriptComponentInstance);
    dlclose(nativeScriptComponentLibrary);
}

void NativeScriptComponentSystem::destroy() {
    ComponentSystem::destroy();
}

void NativeScriptComponentSystem::update(float deltaTime) {
    ComponentSystem::update(deltaTime);
}
