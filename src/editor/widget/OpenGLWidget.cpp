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
#include "src/engine/Input.h"
#include "src/engine/util/KeyCodes.h"

using std::filesystem::current_path;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    setMinimumSize(320, 320);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    cursorLock = false;
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

    if (cursorLock) {
//        QCursor::setPos(0, 0);
    }

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

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    // focus on window on mouse click
    QWidget::setFocus();
    cursorLock = true;
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

    // TODO: handle wheel event by sending to application
};

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    if (cursorLock) {
        if (event->key() == Qt::Key::Key_Escape) {
            cursorLock = false;
        }

        Input::SetButtonDown(event->key(), true);
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    if (cursorLock) {
        Input::SetButtonDown(event->key(), false);
    }
}