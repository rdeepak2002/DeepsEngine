#ifndef OPEN_GL_CUBE_WIDGET_H
#define OPEN_GL_CUBE_WIDGET_H

#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QElapsedTimer"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QObject"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLBuffer"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLFunctions"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtWidgets.framework/Versions/5/Headers/QOpenGLWidget"

#include <glfw3.h>
#include <iostream>

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
//  void createGeometry();
//  void paintTexturedCube();

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

//  qreal m_fAngle = 0;
  qreal m_fScale = 1;
//
//  QOpenGLTexture *m_texture = nullptr;
//  QOpenGLShader *m_vertexShader = nullptr;
//  QOpenGLShader *m_fragmentShader = nullptr;
//  QOpenGLShaderProgram *m_program = nullptr;
//
//  int m_vertexAttr = 0;
//  int m_normalAttr = 0;
//  int m_texCoordAttr = 0;
//  int m_matrixUniform = 0;
//  int m_textureUniform = 0;
//
  QOpenGLBuffer m_buffer;
//  int m_verticesOffset = 0;
//  int m_texCoordsOffset = 0;
//  int m_normalsOffset = 0;
//
  int m_frames = 0;
  QElapsedTimer m_time;
};

#endif
