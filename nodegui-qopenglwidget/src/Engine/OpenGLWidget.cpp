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
  makeCurrent();
//  delete m_program;
//  delete m_vertexShader;
//  delete m_fragmentShader;
//  delete m_texture;
//  m_buffer.destroy();
  doneCurrent();
}

void OpenGLWidget::setScaling(int scale) {
  if (scale > 30)
    m_fScale = 1 + qreal(scale - 30) / 30 * 0.25;
  else if (scale < 30)
    m_fScale = 1 - (qreal(30 - scale) / 30 * 0.25);
  else
    m_fScale = 1;
}

void OpenGLWidget::initializeGL() {
  // TODO QT SPECIFIC:
  ///
  initializeOpenGLFunctions();

  ///

  std::cout << "GLSL VERSION:" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  // glfw: initialize and configure
  // ------------------------------
//  glfwInit();
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

  // glfw window creation
  // --------------------
//  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//  if (window == NULL)
//  {
//    std::cout << "Failed to create GLFW window" << std::endl;
//    glfwTerminate();
//    return -1;
//  }
//  glfwMakeContextCurrent(window);
//  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
//  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//  {
//    std::cout << "Failed to initialize GLAD" << std::endl;
////    return -1;
//  }


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
  //  initializeOpenGLFunctions();
//
//  m_fAngle = 0;
//  m_fScale = 1;
//
//  m_texture = new QOpenGLTexture(QImage("assets/nodegui.jpg"));
//
//  m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
//  m_vertexShader->compileSourceCode(
//      R"SHADER_SRC(
//            attribute highp vec4 vertex;
//            attribute highp vec4 texCoord;
//            attribute mediump vec3 normal;
//            uniform mediump mat4 matrix;
//            varying highp vec4 texc;
//            varying mediump float angle;
//            void main(void)
//            {
//                vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));
//                angle = max(dot(normal, toLight), 0.0);
//                gl_Position = matrix * vertex;
//                texc = texCoord;
//            }
//        )SHADER_SRC");
//
//  m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
//  m_fragmentShader->compileSourceCode(
//      R"SHADER_SRC(
//            varying highp vec4 texc;
//            uniform sampler2D tex;
//            varying mediump float angle;
//            void main(void)
//            {
//                highp vec3 color = texture2D(tex, texc.st).rgb;
//                color = color * 0.2 + color * 0.8 * angle;
//                gl_FragColor = vec4(clamp(color, 0.0, 1.0), 1.0);
//            }
//        )SHADER_SRC");
//
//  m_program = new QOpenGLShaderProgram;
//  m_program->addShader(m_vertexShader);
//  m_program->addShader(m_fragmentShader);
//  m_program->link();
//
//  m_vertexAttr = m_program->attributeLocation("vertex");
//  m_normalAttr = m_program->attributeLocation("normal");
//  m_texCoordAttr = m_program->attributeLocation("texCoord");
//  m_matrixUniform = m_program->uniformLocation("matrix");
//  m_textureUniform = m_program->uniformLocation("tex");
//
//  createGeometry();
}

//void OpenGLWidget::createGeometry() {
//  GLfloat afVertices[] = {
//      -0.5f, +0.5f, +0.5f, +0.5f, -0.5f, +0.5f, -0.5f, -0.5f, +0.5f,
//      +0.5f, -0.5f, +0.5f, -0.5f, +0.5f, +0.5f, +0.5f, +0.5f, +0.5f,
//      -0.5f, -0.5f, -0.5f, +0.5f, -0.5f, -0.5f, -0.5f, +0.5f, -0.5f,
//      +0.5f, +0.5f, -0.5f, -0.5f, +0.5f, -0.5f, +0.5f, -0.5f, -0.5f,
//
//      +0.5f, -0.5f, -0.5f, +0.5f, -0.5f, +0.5f, +0.5f, +0.5f, -0.5f,
//      +0.5f, +0.5f, +0.5f, +0.5f, +0.5f, -0.5f, +0.5f, -0.5f, +0.5f,
//      -0.5f, +0.5f, -0.5f, -0.5f, -0.5f, +0.5f, -0.5f, -0.5f, -0.5f,
//      -0.5f, -0.5f, +0.5f, -0.5f, +0.5f, -0.5f, -0.5f, +0.5f, +0.5f,
//
//      +0.5f, +0.5f, -0.5f, -0.5f, +0.5f, +0.5f, -0.5f, +0.5f, -0.5f,
//      -0.5f, +0.5f, +0.5f, +0.5f, +0.5f, -0.5f, +0.5f, +0.5f, +0.5f,
//      -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, +0.5f, +0.5f, -0.5f, -0.5f,
//      +0.5f, -0.5f, +0.5f, +0.5f, -0.5f, -0.5f, -0.5f, -0.5f, +0.5f,
//  };
//  int numVertices = sizeof(afVertices) / sizeof(GLfloat);
//
//  GLfloat afTexCoords[] = {
//      0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//      1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//
//      1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//      0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//
//      0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//      1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
//  int numTexCoords = sizeof(afTexCoords) / sizeof(GLfloat);
//
//  GLfloat afNormals[] = {
//      +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f,
//      +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f,
//      +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f,
//      +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f,
//
//      -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f,
//      -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f,
//      +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f,
//      +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f,
//
//      +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f,
//      +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f, +0.0f, -1.0f, +0.0f,
//      +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f,
//      +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f, +0.0f, +1.0f, +0.0f};
//  int numNormals = sizeof(afNormals) / sizeof(GLfloat);
//
//  int numFloats = numVertices + numTexCoords + numNormals;
//  m_verticesOffset = 0;
//  m_texCoordsOffset = m_verticesOffset + sizeof(afVertices);
//  m_normalsOffset = m_texCoordsOffset + sizeof(afTexCoords);
//
//  m_buffer.create();
//  m_buffer.bind();
//  m_buffer.allocate(numFloats * sizeof(GLfloat));
//  m_buffer.write(m_verticesOffset, afVertices, sizeof(afVertices));
//  m_buffer.write(m_texCoordsOffset, afTexCoords, sizeof(afTexCoords));
//  m_buffer.write(m_normalsOffset, afNormals, sizeof(afNormals));
//  m_buffer.release();
//}

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
  ///

  // TODO QT SPECIFIC:
  ///
  painter.endNativePainting();
  painter.end();
  update();
  ///

  //  QPainter painter;
//  painter.begin(this);
//
//  painter.beginNativePainting();
//
//  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//  glFrontFace(GL_CW);
//  glCullFace(GL_FRONT);
//  glEnable(GL_CULL_FACE);
//  glEnable(GL_DEPTH_TEST);
//
//  QMatrix4x4 modelView;
//  modelView.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
//  modelView.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
//  modelView.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
//  modelView.scale(m_fScale);
//  modelView.translate(0.0f, -0.2f, 0.0f);
//  m_program->bind();
//  m_program->setUniformValue(m_matrixUniform, modelView);
//  paintTexturedCube();
//  m_program->release();
//
//  glDisable(GL_DEPTH_TEST);
//  glDisable(GL_CULL_FACE);
//
//  painter.endNativePainting();
//
//  if (const int elapsed = m_time.elapsed()) {
//    QString framesPerSecond;
//    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
//    painter.setPen(Qt::black);
//    painter.drawText(20, 40, framesPerSecond + " paintGL calls / s");
//  }
//
//  painter.end();
//
//  if (!(m_frames % 100)) {
//    m_time.start();
//    m_frames = 0;
//  }
//  m_fAngle += 1.0f;
//  ++m_frames;
//
//  update();
}

//void OpenGLWidget::paintTexturedCube() {
//  m_texture->bind();
//
//  m_program->setUniformValue(m_textureUniform, 0);  // use texture unit 0
//
//  m_program->enableAttributeArray(m_vertexAttr);
//  m_program->enableAttributeArray(m_normalAttr);
//  m_program->enableAttributeArray(m_texCoordAttr);
//
//  m_buffer.bind();
//
//  int floatsPerVertex = 3;
//  int floatsPerTexCoord = 2;
//  int floatsPerNormal = 3;
//  int totalFloats = floatsPerVertex + floatsPerTexCoord + floatsPerNormal;
//  int numTriangles = m_buffer.size() / (totalFloats * sizeof(GLfloat));
//
//  m_program->setAttributeBuffer(m_vertexAttr, GL_FLOAT, m_verticesOffset,
//                                floatsPerVertex);
//  m_program->setAttributeBuffer(m_texCoordAttr, GL_FLOAT, m_texCoordsOffset,
//                                floatsPerTexCoord);
//  m_program->setAttributeBuffer(m_normalAttr, GL_FLOAT, m_normalsOffset,
//                                floatsPerNormal);
//
//  m_buffer.release();
//
//  glDrawArrays(GL_TRIANGLES, 0, numTriangles);
//
//  m_program->disableAttributeArray(m_vertexAttr);
//  m_program->disableAttributeArray(m_texCoordAttr);
//  m_program->disableAttributeArray(m_normalAttr);
//}
