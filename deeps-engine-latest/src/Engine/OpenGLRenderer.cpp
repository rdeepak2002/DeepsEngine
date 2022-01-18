//
// Created by Deepak Ramalingam on 1/15/22.
//

#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include "OpenGLRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#if defined(STANDALONE)
// settings
GLFWwindow* window;
#endif

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// unsigned int shaderProgram;
unsigned int VBO, VAO;
unsigned int texture1, texture2;

Shader* ourShader;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

glm::vec3 cameraVelDirection = glm::vec3(0, 0, 0);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

void OpenGLRenderer::initialize() {
#if defined(STANDALONE)
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }
#endif

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);

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
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  // load and create a texture
  // -------------------------
  // texture 1
  // ---------
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
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
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  data = stbi_load("/Users/deepakramalingam/Documents/Projects/deeps-engine/deeps-engine-latest/assets/example-project/textures/awesomeface.png", &width, &height, &nrChannels, 0);
  if (data)
  {
    // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
  // -------------------------------------------------------------------------------------------
  ourShader->use();
  ourShader->setInt("texture1", 0);
  ourShader->setInt("texture2", 1);

  // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
  // -----------------------------------------------------------------------------------------------------------
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
  ourShader->setMat4("projection", projection);
}

void OpenGLRenderer::clear() {
#if !defined(STANDALONE)
  // render
  // ------
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
#endif
}

void OpenGLRenderer::update(float elapsedTime) {
  // TODO: fix issue where editor needs to enable depth test every loop
#if !defined(STANDALONE)
  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);
#endif

  // per-frame time logic
  // --------------------
  float currentFrame = (elapsedTime != 0) ? elapsedTime : static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  // move the camera
  float cameraSpeed = static_cast<float>(2.5 * deltaTime);
  cameraPos += cameraSpeed * cameraVelDirection;

#if defined(STANDALONE)
  processInput(window);
  glfwSetKeyCallback(window, OpenGLRenderer::keyCallback);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

  // render
  // ------
  // bind textures on corresponding texture units
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  // activate shader
  ourShader->use();

  // camera/view transformation
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  ourShader->setMat4("view", view);

  // render boxes
  glBindVertexArray(VAO);
  for (unsigned int i = 0; i < 10; i++)
  {
    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    ourShader->setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

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

#endif
}

void OpenGLRenderer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
#if defined(STANDALONE)
  // TODO: use a set data structure to keep track of which keys should be polled
  // check which key is pressed and send it to be handled
  if (action == GLFW_PRESS) {
    OpenGLRenderer::handleKeyPress(key);
  }
  else if(action == GLFW_RELEASE) {
    OpenGLRenderer::handleKeyRelease(key);
  }
#endif
}

void OpenGLRenderer::handleKeyPress(int keyCode) {
//  std::cout << "character code: " << characterCode << std::endl;
//  std::cout << "camera speed: " << cameraSpeed << std::endl;
//  std::cout << "camera pos: " << "x: " << cameraPos.x << "y: " << cameraPos.y << "z: " << cameraPos.z << std::endl;
  std::cout << "camera velocity direction: " << "x: " << cameraVelDirection.x << "y: " << cameraVelDirection.y << "z: " << cameraVelDirection.z << std::endl;

  if (keyCode == GLFW_KEY_W) {
    std::cout << "pressed w" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
    cameraVelDirection += cameraFront;
  }
  if (keyCode == GLFW_KEY_S) {
    std::cout << "pressed s" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
    cameraVelDirection -= cameraFront;
  }
  if (keyCode == GLFW_KEY_A) {
    std::cout << "pressed a" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
    cameraVelDirection -= glm::normalize(glm::cross(cameraFront, cameraUp));
  }
  if (keyCode == GLFW_KEY_D) {
    std::cout << "pressed d" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
    cameraVelDirection += glm::normalize(glm::cross(cameraFront, cameraUp));
  }
}

void OpenGLRenderer::handleKeyRelease(int keyCode) {
  if (keyCode == GLFW_KEY_W) {
    std::cout << "released w" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
  }
  if (keyCode == GLFW_KEY_S) {
    std::cout << "released s" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
  }
  if (keyCode == GLFW_KEY_A) {
    std::cout << "released a" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
  }
  if (keyCode == GLFW_KEY_D) {
    std::cout << "released d" << std::endl;
    cameraVelDirection = glm::vec3(0, 0, 0);
  }
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