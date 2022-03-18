#include "OpenGLWidget.h"

#include <qmath.h>

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QWidget>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    setMinimumSize(320, 320);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
}

OpenGLWidget::~OpenGLWidget() {
    makeCurrent();
    m_buffer.destroy();
    doneCurrent();
}

void OpenGLWidget::setScaling(int scale) {
    if (scale > 30)
        m_fScale = 1 + qreal(scale - 30) / 30 * 0.25;
    else if (scale < 30)
        m_fScale = 1 - (qreal(30 - scale) / 30 * 0.25);
    else
        m_fScale = 1;
}

void OpenGLWidget::initializeGL() {
    // initialize renderer
    Renderer::getInstance().initialize();

    // create a scene with one entity
    Scene* scene = new Scene();
    scene->createEntity();
    Renderer::getInstance().setScene(scene);
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