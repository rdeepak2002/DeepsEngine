#ifndef OPEN_GL_CUBE_NODE_WIDGET_H
#define OPEN_GL_CUBE_NODE_WIDGET_H

#include <nodegui/core/NodeWidget/nodewidget.h>

#include "OpenGLCubeWidget.h"

class OpenGLCubeNodeGuiWidget : public OpenGLCubeWidget, public NodeWidget {
 public:
  Q_OBJECT;
  NODEWIDGET_IMPLEMENTATIONS(OpenGLCubeWidget)

 public:
  using OpenGLCubeWidget::OpenGLCubeWidget;  // inherit all constructors of
                                             // OpenGLCubeWidget
};

#endif
