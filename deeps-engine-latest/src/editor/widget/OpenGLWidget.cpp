#include "OpenGLWidget.h"

#include <qmath.h>

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QWidget>
#include "src/engine/scene/Entity.h"
#include "src/engine/renderer/Renderer.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    setMinimumSize(320, 320);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
}

OpenGLWidget::~OpenGLWidget() {
    makeCurrent();
    m_buffer.destroy();
    doneCurrent();
}

void OpenGLWidget::resizeEvent(QResizeEvent* ev) {
    QOpenGLWidget::resizeEvent(ev);
    Renderer::getInstance().SCR_WIDTH = width();
    Renderer::getInstance().SCR_HEIGHT = height();
}

void OpenGLWidget::initializeGL() {
    // initialize renderer
    Renderer::getInstance().initialize();
    // create a scene with one entity
    // Renderer::getInstance().scene.CreateEntity();
}

void OpenGLWidget::paintGL() {
    QPainter painter;
    painter.begin(this);

    // clear screen
    Renderer::getInstance().clear();

    // have qt bind its buffer
    m_buffer.bind();

    // draw screen contents
    Renderer::getInstance().update();

    // have qt release its buffer
    m_buffer.release();

    painter.endNativePainting();
    painter.end();

    update();
}