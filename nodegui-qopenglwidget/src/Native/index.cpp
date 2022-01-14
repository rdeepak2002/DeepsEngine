#include <napi.h>

#include "../OpenGLCube/Native/OpenGLNapiWrapper.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  OpenGLNapiWrapper::init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
