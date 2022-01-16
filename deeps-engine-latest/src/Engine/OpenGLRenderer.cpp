//
// Created by Deepak Ramalingam on 1/15/22.
//

#include "OpenGLRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

// unsigned int shaderProgram;
unsigned int VBO, VAO, EBO;
unsigned int texture1, texture2;

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
      // positions          // colors           // texture coords
      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // load and create a texture
  // -------------------------
  // texture 1
  // ---------
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
  // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
  unsigned char *data = stbi_load("/Users/deepakramalingam/Documents/Projects/deeps-engine/deeps-engine-latest/assets/example-project/textures/container.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  // texture 2
  // ---------
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  data = stbi_load("/Users/deepakramalingam/Documents/Projects/deeps-engine/deeps-engine-latest/assets/example-project/textures/awesomeface.png", &width, &height, &nrChannels, 0);
  if (data)
  {
    // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
  // -------------------------------------------------------------------------------------------
  ourShader->use(); // don't forget to activate/use the shader before setting uniforms!
  // either set it manually like so:
  glUniform1i(glGetUniformLocation(ourShader->ID, "texture1"), 0);
  // or set it via the texture class
  ourShader->setInt("texture2", 1);
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

  // render
  // ------
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // bind textures on corresponding texture units
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  // render container
  ourShader->use();
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
  glDeleteBuffers(1, &EBO);
  delete ourShader;
  ourShader = nullptr;
  glfwTerminate();
#endif
}