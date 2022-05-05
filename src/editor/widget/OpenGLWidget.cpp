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
        setMouseTracking(true);

        if (!underMouse()) {
            moveMouseToCenter();
        }
    } else {
        setMouseTracking(false);
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
    hideCursor();
    std::cout << "mouse pressed x: " << event->x() << std::endl;
    std::cout << "mouse pressed y: " << event->y() << std::endl;

    if (cursorLock) {
        // TODO: send this to engine

    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "mouse released x: " << event->x() << std::endl;
    std::cout << "mouse released y: " << event->y() << std::endl;

    if (cursorLock) {
        // TODO: send this to engine

    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    std::cout << "mouse moved x: " << event->x() << std::endl;
    std::cout << "mouse moved y: " << event->y() << std::endl;

    if (cursorLock) {
        // TODO: send this to engine

        moveMouseToCenter();
    }
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
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
    int hardcodedEscapeCode = 16777216;

    if (event->key() == Qt::Key::Key_Escape || event->key() == hardcodedEscapeCode) {
        cursorLock = false;
        showCursor();
    }

    if (cursorLock) {
        Input::SetButtonDown(event->key(), true);
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    if (cursorLock) {
        Input::SetButtonDown(event->key(), false);
    }
}

void OpenGLWidget::leaveEvent(QEvent *event) {
    if (cursorLock) {
        hideCursor();
        moveMouseToCenter();
    }
}

void OpenGLWidget::moveMouseToCenter() {
    QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
    QCursor::setPos(glob);
}

void OpenGLWidget::hideCursor() {
    setCursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(Qt::BlankCursor);
}

void OpenGLWidget::showCursor() {
    unsetCursor();
    QApplication::restoreOverrideCursor();
}
