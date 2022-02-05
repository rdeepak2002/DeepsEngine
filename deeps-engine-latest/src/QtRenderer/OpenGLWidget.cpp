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

int OpenGLWidget::createEntity() {
  std::cout << "creating entity" << std::endl;
  int result = OpenGLRenderer::createEntity();
  return result;
}

std::vector<u_int32_t> OpenGLWidget::getEntities() {
  std::vector<u_int32_t> result = OpenGLRenderer::getEntities();

  return result;
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

  m_time_master.start();
}

void OpenGLWidget::paintGL() {
  // TODO: only request focus when necessary
//  QWidget::setFocus();

  // have qt begin its painting
  QPainter painter;
  painter.begin(this);

  // clear opengl screen
  OpenGLRenderer::clear();

  // have qt bind its buffer
  m_buffer.bind();

  float elapsedTime = static_cast<float>(m_time_master.elapsed()/1000.0);

  // have the opengl renderer update
  OpenGLRenderer::update(elapsedTime);

  // have qt release its buffer
  m_buffer.release();

  // stop qt painting and count fps
  painter.endNativePainting();

  if (const int elapsed = m_time.elapsed()) {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::black);
    painter.drawText(20, 40, framesPerSecond + " fps (v2)");
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

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
  // focus on window on mouse click
  QWidget::setFocus();
  // TODO: send this to engine
  std::cout << "mouse pressed x: " << event->x() << std::endl;
  std::cout << "mouse pressed y: " << event->y() << std::endl;
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
  // focus on window on mouse click
  // TODO: send this to engine
  std::cout << "mouse released x: " << event->x() << std::endl;
  std::cout << "mouse released y: " << event->y() << std::endl;
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  // TODO: send this to engine
  std::cout << "mouse moved x: " << event->x() << std::endl;
  std::cout << "mouse moved y: " << event->y() << std::endl;
};
void OpenGLWidget::wheelEvent(QWheelEvent *event) {
  // TODO: send this to engine
  QPoint numPixels = event->pixelDelta();
  QPoint numDegrees = event->angleDelta() / 8;

  int dx, dy;

  if (!numPixels.isNull()) {
    dx = numPixels.x();
    dy = numPixels.y();
  } else if (!numDegrees.isNull()) {
    QPoint numSteps = numDegrees / 15;
    dx = numSteps.x();
    dy = numSteps.y();
  }

  OpenGLRenderer::handleScroll(dx, dy);
};

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
  OpenGLRenderer::handleKeyPress(event->key());
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
  OpenGLRenderer::handleKeyRelease(event->key());
}
