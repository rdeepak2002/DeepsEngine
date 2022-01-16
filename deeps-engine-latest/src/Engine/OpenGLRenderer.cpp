//
// Created by Deepak Ramalingam on 1/15/22.
//

#include "OpenGLRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

// unsigned int shaderProgram;
unsigned int VBO, VAO;

#if defined(STANDALONE)
// settings
GLFWwindow* window;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
#endif

Shader* ourShader;

void OpenGLRenderer::initialize() {
#if defined(STANDALONE)
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }
#endif

  ourShader = new Shader(
      "/Users/deepakramalingam/Documents/Projects/deeps-engine/"
      "deeps-engine-latest/assets/example-project/shaders/shader.vert",
      "/Users/deepakramalingam/Documents/Projects/deeps-engine/"
      "deeps-engine-latest/assets/example-project/shaders/shader.frag");  // you
                                                                          // can
                                                                          // name
                                                                          // your
                                                                          // shader
                                                                          // files
                                                                          // however
                                                                          // you
                                                                          // like

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      // positions         // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void OpenGLRenderer::clear() {
#if !defined(STANDALONE)
  // render
  // ------
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
#endif
}

void OpenGLRenderer::update() {
#if defined(STANDALONE)
  processInput(window);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
#endif

  // render the triangle
  ourShader->use();
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

#if defined(STANDALONE)
  glfwSwapBuffers(window);
  glfwPollEvents();
#endif
}

void OpenGLRenderer::createWindow() {
#if defined(STANDALONE)
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#endif
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void OpenGLRenderer::processInput(GLFWwindow* window) {
#if defined(STANDALONE)
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
#endif
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void OpenGLRenderer::framebuffer_size_callback(GLFWwindow* window, int width,
                                               int height) {
#if defined(STANDALONE)
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
#endif
}

bool OpenGLRenderer::shouldCloseWindow() {
#if defined(STANDALONE)
  if (window) {
    return glfwWindowShouldClose(window);
  } else {
    return true;
  }
#else
  return false;
#endif
}

void OpenGLRenderer::closeWindow() {
#if defined(STANDALONE)
  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  delete ourShader;
  ourShader = nullptr;
  glfwTerminate();
#endif
}