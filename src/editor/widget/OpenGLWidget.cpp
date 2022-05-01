#include "OpenGLWidget.h"

#include <qmath.h>

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QWidget>
#include "src/engine/scene/Entity.h"
#include "src/engine/renderer/Renderer.h"
#include "src/engine/component/Component.h"
#include "src/engine/Application.h"

using std::filesystem::current_path;

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
    Application::getInstance().resizeWindow(width(), height(), false);
}

void OpenGLWidget::initializeGL() {
    // initialize renderer
    Application::getInstance().initialize();
}

void OpenGLWidget::paintGL() {
    QPainter painter;
    painter.begin(this);

    // clear screen
    Application::getInstance().clearRenderer();

    // have qt bind its buffer
    m_buffer.bind();

    // draw screen contents
    Application::getInstance().update(false);

    // have qt release its buffer
    m_buffer.release();

    painter.endNativePainting();
    painter.end();

    update();
}