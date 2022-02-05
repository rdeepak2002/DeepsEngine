#include "OpenGLCubeWidget.h"

#include <qmath.h>

#include <QDebug>
#include <QDir>
#include <QImage>
#include <QMatrix4x4>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QPainter>
#include <QString>
#include <QWidget>

#include <iostream>

OpenGLCubeWidget::OpenGLCubeWidget(QWidget *parent) : QOpenGLWidget(parent) {
    setMinimumSize(320, 320);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);

//#ifdef GL_SRGB8_ALPHA8
//    setTextureFormat(GL_SRGB8_ALPHA8);
//#endif
}

OpenGLCubeWidget::~OpenGLCubeWidget() {
    makeCurrent();
    m_buffer.destroy();
    doneCurrent();
}

void OpenGLCubeWidget::setScaling(int scale) {
    if (scale > 30)
        m_fScale = 1 + qreal(scale - 30) / 30 * 0.25;
    else if (scale < 30)
        m_fScale = 1 - (qreal(30 - scale) / 30 * 0.25);
    else
        m_fScale = 1;
}

void OpenGLCubeWidget::initializeGL() {
    // initialize renderer
    renderer.initialize();
}

void OpenGLCubeWidget::paintGL() {
    QPainter painter;
    painter.begin(this);

    // clear screen
    renderer.clear();

    // have qt bind its buffer
    m_buffer.bind();

    // draw screen contents
    renderer.update();

    // have qt release its buffer
    m_buffer.release();

    painter.endNativePainting();
    painter.end();

    update();
}