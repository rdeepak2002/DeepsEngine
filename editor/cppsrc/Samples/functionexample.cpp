#include "functionexample.h"

std::string functionexample::hello(){
  return "Hello World from NAPI";
}

Napi::String functionexample::HelloWrapped(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1 || !info[0].IsNumber()) {
     Napi::TypeError::New(env, "Numberexpected").ThrowAsJavaScriptException();
  }
  Napi::Number num = info[0].As<Napi::Number>();

  Napi::String returnValue = Napi::String::New(env, functionexample::hello());

  return returnValue;
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
"hello", Napi::Function::New(env, functionexample::HelloWrapped)
  );

  return exports;
}
