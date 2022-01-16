#ifndef OPEN_GL_CUBE_NODE_WIDGET_H
#define OPEN_GL_CUBE_NODE_WIDGET_H

#include "node_modules/@nodegui/nodegui/src/cpp/include/nodegui/core/NodeWidget/nodewidget.h"

#include "OpenGLWidget.h"

class OpenGLNodeGuiWidget : public OpenGLWidget, public NodeWidget {
 public:
  Q_OBJECT;
  NODEWIDGET_IMPLEMENTATIONS(OpenGLWidget)

 public:
  using OpenGLWidget::OpenGLWidget;  // inherit all constructors of
                                             // OpenGLWidget
};

#endif
