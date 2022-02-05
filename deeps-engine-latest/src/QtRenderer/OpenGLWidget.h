#ifndef OPEN_GL_CUBE_WIDGET_H
#define OPEN_GL_CUBE_WIDGET_H

#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QElapsedTimer"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QObject"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLBuffer"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLFunctions"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QKeyEvent"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QMouseEvent"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QWheelEvent"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtWidgets.framework/Versions/5/Headers/QOpenGLWidget"

#include "../Engine/OpenGLRenderer.h"

QT_FORWARD_DECLARE_CLASS(QWidget)

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

 public:
  explicit OpenGLWidget(QWidget *parent = nullptr);
  ~OpenGLWidget();
  int createEntity();

 public slots:
  void setScaling(int scale);

 protected:
  // initialize opengl
  void initializeGL() override;
  // paint method called every update loop
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 private:
  // keep track of scale
  qreal m_fScale = 1;
  // count number of frames and keep track of glbuffer
  QOpenGLBuffer m_buffer;
  int m_frames = 0;
  QElapsedTimer m_time;
  QElapsedTimer m_time_master;
};

#endif
