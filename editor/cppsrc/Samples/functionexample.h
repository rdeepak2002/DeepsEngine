#include <napi.h>

namespace functionexample {
  std::string hello(int num);
  Napi::String HelloWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
