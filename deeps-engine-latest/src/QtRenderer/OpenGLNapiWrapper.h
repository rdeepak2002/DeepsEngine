#ifndef OPEN_GL_CUBE_NAPI_WRAPPER_H
#define OPEN_GL_CUBE_NAPI_WRAPPER_H

#include "node_modules/node-addon-api/napi.h"
#include "node_modules/@nodegui/nodegui/src/cpp/include/nodegui/QtWidgets/QWidget/qwidget_macro.h"

#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QPointer"

#include "OpenGLNodeGuiWidget.h"

class OpenGLNapiWrapper : public Napi::ObjectWrap<OpenGLNapiWrapper> {
  QPointer<OpenGLNodeGuiWidget> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);

  OpenGLNapiWrapper(const Napi::CallbackInfo &info);
  ~OpenGLNapiWrapper();

  OpenGLNodeGuiWidget *getInternalInstance();

  // wrapped methods
  Napi::Value testMessage(const Napi::CallbackInfo &info);
  Napi::Value createEntity(const Napi::CallbackInfo &info);
  Napi::Value getEntities(const Napi::CallbackInfo &info);

  QWIDGET_WRAPPED_METHODS_DECLARATION
};

#endif
