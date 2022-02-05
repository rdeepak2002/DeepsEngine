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
    void createGeometry();
    void paintTexturedCube();

    qreal m_fAngle = 0;
    qreal m_fScale = 1;

    QOpenGLTexture *m_texture = nullptr;
    QOpenGLShader *m_vertexShader = nullptr;
    QOpenGLShader *m_fragmentShader = nullptr;
    QOpenGLShaderProgram *m_program = nullptr;

    int m_vertexAttr = 0;
    int m_normalAttr = 0;
    int m_texCoordAttr = 0;
    int m_matrixUniform = 0;
    int m_textureUniform = 0;

    QOpenGLBuffer m_buffer;
    int m_verticesOffset = 0;
    int m_texCoordsOffset = 0;
    int m_normalsOffset = 0;

    int m_frames = 0;
    QElapsedTimer m_time;

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    unsigned int shaderProgram;
    unsigned int VBO, VAO;
};


#endif //EXAMPLE_OPENGLCUBEWIDGET_H
