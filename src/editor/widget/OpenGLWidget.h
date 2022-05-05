//
// Created by Deepak Ramalingam on 2/5/22.
//

#ifndef EXAMPLE_OPENGLCUBEWIDGET_H
#define EXAMPLE_OPENGLCUBEWIDGET_H


#include <QElapsedTimer>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>

QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QWidget)

//#include "src/engine/renderer/Renderer.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
Q_OBJECT;

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeEvent(QResizeEvent* ev) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QOpenGLBuffer m_buffer;
    bool cursorLock;
};


#endif //EXAMPLE_OPENGLCUBEWIDGET_H
