#ifndef OPEN_GL_CUBE_NAPI_WRAPPER_H
#define OPEN_GL_CUBE_NAPI_WRAPPER_H

#include <napi.h>
#include <nodegui/QtWidgets/QWidget/qwidget_macro.h>

#include <QPointer>

#include "OpenGLCubeNodeGuiWidget.h"

class OpenGLCubeNapiWrapper : public Napi::ObjectWrap<OpenGLCubeNapiWrapper> {
  QPointer<OpenGLCubeNodeGuiWidget> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);

  OpenGLCubeNapiWrapper(const Napi::CallbackInfo &info);
  ~OpenGLCubeNapiWrapper();

  OpenGLCubeNodeGuiWidget *getInternalInstance();

  // wrapped methods
  Napi::Value testMessage(const Napi::CallbackInfo &info);

  QWIDGET_WRAPPED_METHODS_DECLARATION
};

#endif
