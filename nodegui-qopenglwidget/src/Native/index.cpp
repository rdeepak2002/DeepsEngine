#include <napi.h>

#include "../OpenGLCube/Native/OpenGLCubeNapiWrapper.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  OpenGLCubeNapiWrapper::init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
