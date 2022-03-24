#include "OpenGLWidget.h"

#include <qmath.h>

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QWidget>
#include "src/engine/scene/Entity.h"
#include "src/engine/renderer/Renderer.h"
#include "src/engine/component/Component.h"

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
    // create basic scene
    // add camera entity
    DeepsEngine::Entity camera = Renderer::getInstance().scene.CreateEntity("Main Camera");
    (&camera.GetComponent<DeepsEngine::Component::Transform>())->position.z = 5.0;
    camera.AddComponent<DeepsEngine::Component::Camera>(DeepsEngine::Component::Camera({45.0f, 0.1f, 100.0f}));

    // add a single cube entity
    DeepsEngine::Entity entity = Renderer::getInstance().scene.CreateEntity("Cube");
    entity.AddComponent<DeepsEngine::Component::MeshFilter>(DeepsEngine::Component::MeshFilter{"cube"});
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