#include "OpenGLWidget.h"

#include <qmath.h>

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QWidget>
#include "Entity.h"
#include "Renderer.h"
#include "Component.h"
#include "Application.h"
#include "Input.h"

using std::filesystem::current_path;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    setMinimumSize(320, 320);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    cursorLock = false;

    // define weird key codes from QT
    specialKeysMap[16777216] = DeepsEngine::Key::Escape;
    specialKeysMap[Qt::Key::Key_Escape] = DeepsEngine::Key::Escape;

    specialKeysMap[16777234] = DeepsEngine::Key::Right;
    specialKeysMap[Qt::Key::Key_Right] = DeepsEngine::Key::Right;

    specialKeysMap[16777234] = DeepsEngine::Key::Left;
    specialKeysMap[Qt::Key::Key_Left] = DeepsEngine::Key::Left;

    specialKeysMap[16777237] = DeepsEngine::Key::Down;
    specialKeysMap[Qt::Key::Key_Down] = DeepsEngine::Key::Down;

    specialKeysMap[16777235] = DeepsEngine::Key::Up;
    specialKeysMap[Qt::Key::Key_Up] = DeepsEngine::Key::Up;

    specialKeysMap[16777248] = DeepsEngine::Key::LeftShift;
    specialKeysMap[Qt::Key::Key_Shift] = DeepsEngine::Key::LeftShift;
}

OpenGLWidget::~OpenGLWidget() {
    makeCurrent();
    m_buffer.destroy();
    doneCurrent();
    Application::getInstance().close();
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
    if (specialKeysMap.count(event->key()) > 0 && specialKeysMap[event->key()] == DeepsEngine::Key::Escape) {
        cursorLock = false;
        showCursor();
    }

    bool newKeyStateValue = true;

    if (cursorLock) {
        if (specialKeysMap.count(event->key()) > 0) {
            Input::SetButtonDown(specialKeysMap[event->key()], newKeyStateValue);
        } else {
            Input::SetButtonDown(event->key(), newKeyStateValue);
        }
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    bool newKeyStateValue = false;

    if (cursorLock) {
        if (specialKeysMap.count(event->key()) > 0) {
            Input::SetButtonDown(specialKeysMap[event->key()], newKeyStateValue);
        } else {
            Input::SetButtonDown(event->key(), newKeyStateValue);
        }
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
