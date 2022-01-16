#include "OpenGLWidget.h"

#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QPainter"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QString"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtWidgets.framework/Versions/5/Headers/QWidget"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  // qt define widget attributes
  setMinimumSize(320, 320);
  setAttribute(Qt::WA_AlwaysStackOnTop, true);

//#ifdef GL_SRGB8_ALPHA8
//  setTextureFormat(GL_SRGB8_ALPHA8);
//#endif
}

OpenGLWidget::~OpenGLWidget() {
  // qt cleanup
  makeCurrent();
  m_buffer.destroy();
  doneCurrent();
}

void OpenGLWidget::setScaling(int scale) {
  // scaling for qt widget
  if (scale > 30)
    m_fScale = 1 + qreal(scale - 30) / 30 * 0.25;
  else if (scale < 30)
    m_fScale = 1 - (qreal(30 - scale) / 30 * 0.25);
  else
    m_fScale = 1;
}

void OpenGLWidget::initializeGL() {
  // have qt initialize opengl functions
  initializeOpenGLFunctions();

  OpenGLRenderer::initialize();
}

void OpenGLWidget::paintGL() {
  // have qt begin its painting
  QPainter painter;
  painter.begin(this);

  // clear opengl screen
  OpenGLRenderer::clear();

  // have qt bind its buffer
  m_buffer.bind();

  // have the opengl renderer update
  OpenGLRenderer::update();

  // have qt release its buffer
  m_buffer.release();

  // stop qt painting and count fps
  painter.endNativePainting();

  if (const int elapsed = m_time.elapsed()) {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::black);
    painter.drawText(20, 40, framesPerSecond + " fps (v1)");
  }

  painter.end();

  if (!(m_frames % 100)) {
    m_time.start();
    m_frames = 0;
  }
  ++m_frames;

  // have this qt widget update
  update();
}