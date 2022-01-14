#ifndef OPEN_GL_CUBE_WIDGET_H
#define OPEN_GL_CUBE_WIDGET_H

#include <QElapsedTimer>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QWidget)

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

 public:
  explicit OpenGLWidget(QWidget *parent = nullptr);
  ~OpenGLWidget();

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
};

#endif
