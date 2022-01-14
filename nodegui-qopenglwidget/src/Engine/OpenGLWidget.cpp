//#include <glad.h>
#include "OpenGLWidget.h"

#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/qmath.h"

#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QDebug"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QDir"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QImage"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QMatrix4x4"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLShader"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLTexture"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QPainter"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtCore.framework/Versions/5/Headers/QString"
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtWidgets.framework/Versions/5/Headers/QWidget"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  setMinimumSize(320, 320);
  setAttribute(Qt::WA_AlwaysStackOnTop, true);

//#ifdef GL_SRGB8_ALPHA8
//  setTextureFormat(GL_SRGB8_ALPHA8);
//#endif
}

OpenGLWidget::~OpenGLWidget() {
  // TODO QT SPECIFIC:
  ///
  makeCurrent();
  m_buffer.destroy();
  doneCurrent();
  ///
}

void OpenGLWidget::setScaling(int scale) {
  // TODO QT SPECIFIC:
  ///
  if (scale > 30)
    m_fScale = 1 + qreal(scale - 30) / 30 * 0.25;
  else if (scale < 30)
    m_fScale = 1 - (qreal(30 - scale) / 30 * 0.25);
  else
    m_fScale = 1;
  ///
}

void OpenGLWidget::initializeGL() {
  // TODO QT SPECIFIC:
  ///
  initializeOpenGLFunctions();
  ///

  std::cout << "GLSL VERSION:" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // link shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // left
      0.5f, -0.5f, 0.0f, // right
      0.0f,  0.5f, 0.0f  // top
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);
}

void OpenGLWidget::paintGL() {
  // TODO QT SPECIFIC:
  ///
  QPainter painter;
  painter.begin(this);
  ///

  // input
  // -----
//  processInput(window);

  // render
  // ------
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // TODO QT SPECIFIC:
  ///
  m_buffer.bind();
  ///

  // draw our first triangle
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
  glDrawArrays(GL_TRIANGLES, 0, 3);
  // glBindVertexArray(0); // no need to unbind it every time

  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
  // -------------------------------------------------------------------------------
//  glfwSwapBuffers(window);
//  glfwPollEvents();

  // TODO QT SPECIFIC:
  ///
  m_buffer.release();

  painter.endNativePainting();

  if (const int elapsed = m_time.elapsed()) {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::black);
    painter.drawText(20, 40, framesPerSecond + " paintGL calls / s");
  }

  painter.end();

  if (!(m_frames % 100)) {
    m_time.start();
    m_frames = 0;
  }
  ++m_frames;

  update();
  ///
}