#include "bindings.h"
#include "../src/Renderer.h"

#include <thread>

Renderer *renderer;

std::string bindings::checkEngineStatus(int num) {
    return "Engine Running, received input " + std::to_string(num);
}

void bindings::createRenderer(bool showWindow, bool saveOutputRender, std::string projectPath) {
    if (renderer)
        renderer->shutDown();

    renderer = new Renderer(showWindow, saveOutputRender, projectPath);

    renderer->init();

    // TODO: remove this
//    std::string newEntityGuid = renderer->addEntity("cube");
}

bool bindings::rendererShuttingDown() {
    if (!renderer)
        return true;
    return renderer->shuttingDown();
}

void bindings::updateRenderer() {
    if (renderer)
        renderer->render();
}

void bindings::shutDownRenderer() {
    if (renderer)
        renderer->shutDown();
}

std::string bindings::getCachedFrame() {
    std::string res = "no frame";

    if (renderer && !renderer->cachedFrame.empty()) {
        res = renderer->cachedFrame;
    }

    return res;
}

void bindings::handleEditorResize(int width, int height) {
    if (renderer)
        renderer->handleEditorResize(width, height);
}

void bindings::startPlayMode() {
    if(renderer) {
        // TODO: remove this
//        std::string newEntityGuid = renderer->addEntity("cube");

        while(!renderer->shuttingDown()) {
            renderer->render();
        }
    }
}

void bindings::addEntity(std::string name) {
    if(renderer) {
        std::string newEntityGuid = renderer->addEntity(name);
    }
}

void bindings::updateComponent(std::uint32_t entity, std::string json) {
    if(renderer) {
        renderer->updateComponent(entity, json);
    }
}

int bindings::getNumEntities() {
    if(renderer) {
        return renderer->entities.size();
    }

    return 0;
}

int* bindings::getEntities(int entitiesArr[]) {
    if(renderer) {
        std::copy(renderer->entities.begin(), renderer->entities.end(), entitiesArr);
        return entitiesArr;
    }

    return nullptr;
}

void bindings::handleEditorDragging(float dx, float dy) {
    if(renderer) {
        renderer->handleEditorDragging(dx, dy);
    }
}

Napi::String bindings::GetCachedFrameWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::String returnValue = Napi::String::New(env, bindings::getCachedFrame());

    return returnValue;
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

    if (info.Length() != 3) {
        if (!info[0].IsBoolean()) {
            Napi::TypeError::New(env, "Boolean expected for show window").ThrowAsJavaScriptException();
        }

        if (!info[1].IsBoolean()) {
            Napi::TypeError::New(env, "Boolean expected for save output render").ThrowAsJavaScriptException();
        }

        if (!info[2].IsBoolean()) {
            Napi::TypeError::New(env, "String expected for engine path").ThrowAsJavaScriptException();
        }
    }

    Napi::Boolean showWindow = info[0].As<Napi::Boolean>();
    Napi::Boolean saveOutputRender = info[1].As<Napi::Boolean>();
    Napi::String projectPath = info[2].As<Napi::String>();

    bindings::createRenderer(showWindow.Value(), saveOutputRender.Value(), projectPath.Utf8Value());
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

void bindings::HandleEditorResizeWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 2) {
        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "Width expected for resizing editor window").ThrowAsJavaScriptException();
        }

        if (!info[1].IsNumber()) {
            Napi::TypeError::New(env, "Height expected for resizing editor window").ThrowAsJavaScriptException();
        }
    }

    Napi::Number width = info[0].As<Napi::Number>();
    Napi::Number height = info[1].As<Napi::Number>();

    bindings::handleEditorResize(width.Int64Value(), height.Int64Value());
}

void bindings::StartPlayModeWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bindings::startPlayMode();
}

void bindings::AddEntityWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1) {
        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "Name expected for entity").ThrowAsJavaScriptException();
        }
    }

    Napi::String name = info[0].As<Napi::String>();
    bindings::addEntity(name.Utf8Value());
}

Napi::Uint8Array bindings::GetEntitiesWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int numEntities = bindings::getNumEntities();
    int entitiesArr[numEntities];

    if(bindings::getEntities(entitiesArr)) {
        Napi::Uint8Array arr = Napi::Uint8Array::New(info.Env(), numEntities);

        for(int i = 0; i < numEntities; i++) {
            arr[i] = (u_int8_t)entitiesArr[i];
        }

        return arr;
    }

    Napi::Uint8Array emptyArr = Napi::Uint8Array ::New(info.Env(), 0);

    return emptyArr;
}

void bindings::UpdateComponentWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 2) {
        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "Entity id expected").ThrowAsJavaScriptException();
        }
        if (!info[1].IsString()) {
            Napi::TypeError::New(env, "Component update JSON expected").ThrowAsJavaScriptException();
        }
    }

    Napi::Number entityId = info[0].As<Napi::Number>();
    Napi::String json = info[1].As<Napi::String>();

    bindings::updateComponent(entityId.Int64Value(), json.Utf8Value());
}
void bindings::HandleEditorDraggingWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 2) {
        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "dx expected").ThrowAsJavaScriptException();
        }
        if (!info[1].IsNumber()) {
            Napi::TypeError::New(env, "dy expected").ThrowAsJavaScriptException();
        }
    }

    Napi::Number dx = info[0].As<Napi::Number>();
    Napi::Number dy = info[1].As<Napi::Number>();

    bindings::handleEditorDragging(dx.FloatValue(), dy.FloatValue());
}


Napi::Object bindings::Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
            "checkEngineStatus", Napi::Function::New(env, bindings::CheckEngineStatusWrapped)
    );

    exports.Set("getCachedFrame", Napi::Function::New(env, bindings::GetCachedFrameWrapped));

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

    exports.Set(
            "handleEditorResize", Napi::Function::New(env, bindings::HandleEditorResizeWrapped)
    );

    exports.Set(
            "startPlayMode", Napi::Function::New(env, bindings::StartPlayModeWrapped)
    );

    exports.Set(
            "addEntity", Napi::Function::New(env, bindings::AddEntityWrapped)
    );

    exports.Set(
            "updateComponent", Napi::Function::New(env, bindings::UpdateComponentWrapped)
    );

    exports.Set(
            "getEntities", Napi::Function::New(env, bindings::GetEntitiesWrapped)
    );

    exports.Set(
            "handleEditorDragging", Napi::Function::New(env, bindings::HandleEditorDraggingWrapped)
    );

    return exports;
}
