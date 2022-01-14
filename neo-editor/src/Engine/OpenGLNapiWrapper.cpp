#include "OpenGLNapiWrapper.h"

#include "node_modules/@nodegui/nodegui/src/cpp/include/nodegui/Extras/Utils/nutils.h"
#include "node_modules/@nodegui/nodegui/src/cpp/include/nodegui/QtWidgets/QWidget/qwidget_wrap.h"

#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtWidgets.framework/Versions/5/Headers/QWidget"

Napi::FunctionReference OpenGLNapiWrapper::constructor;

Napi::Object OpenGLNapiWrapper::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  const char CLASSNAME[] = "OpenGLCube";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("test", &OpenGLNapiWrapper::testMessage),
       QWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(OpenGLNapiWrapper)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

OpenGLNodeGuiWidget *OpenGLNapiWrapper::getInternalInstance() {
  return this->instance;
}

OpenGLNapiWrapper::OpenGLNapiWrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<OpenGLNapiWrapper>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  // set gl version
  QSurfaceFormat glFormat;
  glFormat.setVersion(3, 3);
  glFormat.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(glFormat);

  if (info.Length() == 1) {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    OpenGLNapiWrapper *parentWrapper =
        Napi::ObjectWrap<OpenGLNapiWrapper>::Unwrap(parentObject);
    this->instance =
        new OpenGLNodeGuiWidget(parentWrapper->getInternalInstance());
  } else if (info.Length() == 0) {
    this->instance = new OpenGLNodeGuiWidget();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureQWidget(
      this->getInternalInstance(), this->getInternalInstance()->getFlexNode(),
      true);
}

OpenGLNapiWrapper::~OpenGLNapiWrapper() {
  extrautils::safeDelete(this->instance);
}

Napi::Value OpenGLNapiWrapper::testMessage(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  //  Napi::String message = info[0].As<Napi::String>();
  //  Napi::Number timeout = info[1].As<Napi::Number>();
  //  this->instance->testMessage(QString::fromStdString(message.Utf8Value()),
  //                              timeout.Int32Value());

  return Napi::String::New(env, "Hello, World!");
}
