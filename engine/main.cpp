#include <napi.h>
#include "EditorBinding/functionexample.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return functionexample::Init(env, exports);
}

NODE_API_MODULE(testaddon, InitAll);