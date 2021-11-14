#include <napi.h>

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>

namespace functionexample {
  std::string hello(int num);
  Napi::String HelloWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
