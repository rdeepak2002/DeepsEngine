#include "OpenGLCubeNapiWrapper.h"

#include <nodegui/Extras/Utils/nutils.h>
#include <nodegui/QtWidgets/QWidget/qwidget_wrap.h>

#include <QWidget>

Napi::FunctionReference OpenGLCubeNapiWrapper::constructor;

Napi::Object OpenGLCubeNapiWrapper::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  const char CLASSNAME[] = "OpenGLCube";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("test", &OpenGLCubeNapiWrapper::testMessage),
       QWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(OpenGLCubeNapiWrapper)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

OpenGLCubeNodeGuiWidget *OpenGLCubeNapiWrapper::getInternalInstance() {
  return this->instance;
}

OpenGLCubeNapiWrapper::OpenGLCubeNapiWrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<OpenGLCubeNapiWrapper>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 1) {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    OpenGLCubeNapiWrapper *parentWrapper =
        Napi::ObjectWrap<OpenGLCubeNapiWrapper>::Unwrap(parentObject);
    this->instance =
        new OpenGLCubeNodeGuiWidget(parentWrapper->getInternalInstance());
  } else if (info.Length() == 0) {
    this->instance = new OpenGLCubeNodeGuiWidget();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureQWidget(
      this->getInternalInstance(), this->getInternalInstance()->getFlexNode(),
      true);
}

OpenGLCubeNapiWrapper::~OpenGLCubeNapiWrapper() {
  extrautils::safeDelete(this->instance);
}

Napi::Value OpenGLCubeNapiWrapper::testMessage(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  //  Napi::String message = info[0].As<Napi::String>();
  //  Napi::Number timeout = info[1].As<Napi::Number>();
  //  this->instance->testMessage(QString::fromStdString(message.Utf8Value()),
  //                              timeout.Int32Value());

  return Napi::String::New(env, "Hello, World!");
}
