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

QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QWidget)

//#include "../Engine/OpenGLRenderer.h"
#include "../Engine/Renderer.h"

class OpenGLCubeWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
Q_OBJECT;

public:
    explicit OpenGLCubeWidget(QWidget *parent = nullptr);
    ~OpenGLCubeWidget();

public slots:
    void setScaling(int scale);

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    qreal m_fAngle = 0;
    qreal m_fScale = 1;
    QOpenGLBuffer m_buffer;
    Renderer renderer;
};


#endif //EXAMPLE_OPENGLCUBEWIDGET_H
