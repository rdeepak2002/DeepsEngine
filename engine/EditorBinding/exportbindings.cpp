#include <napi.h>
#include "bindings.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return bindings::Init(env, exports);
}

NODE_API_MODULE(testaddon, InitAll);