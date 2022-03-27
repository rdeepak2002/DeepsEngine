#if defined(STANDALONE)

#if defined(EMSCRIPTEN) or defined(DEVELOP_WEB)

#include <iostream>

// Include the EMSCRIPTEN specific headers
#ifdef EMSCRIPTEN
#include <emscripten.h>
#include <GLFW/glfw3.h>
#else
#include <glfw3.h>
#endif

// For example purpose we use global variables
#define SPEED 0.005f
GLFWwindow* window = nullptr;
float red = 0.0f;
bool increase = true;

/**
 * @brief This function just increases and decreases the red value.
 *
 * @return The red value.
 */
float getRed() {
    if (increase) {
        red += SPEED;
        if (red > 1.0f) {
            red = 1.0f;
            increase = false;
        }
    } else {
        red -= SPEED;
        if (red < 0.0f) {
            red = 0.0f;
            increase = true;
        }
    }

    return red;
}

/**
 * @brief This function is called every frame.
 */
void mainLoop() {
    // Clear the screen with a color
    glClearColor(getRed(), 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the buffers of the window
    glfwSwapBuffers(window);

    // Poll for the events
    glfwPollEvents();
}

/**
 * @brief The normal main() function.
 *
 * @return Exit code.
 */
int main() {
    std::cout << "Starting" << std::endl;

    // Initialize glfw
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // Create the window
    window = glfwCreateWindow(640, 480, "Emscripten webgl example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Make this window the current context
    glfwMakeContextCurrent(window);

    std::cout << "Going into loop" << std::endl;
#ifdef EMSCRIPTEN
    // Define a mail loop function, that will be called as fast as possible
    emscripten_set_main_loop(&mainLoop, 0, 1);
#else
    // This is the normal C/C++ main loop
    while (!glfwWindowShouldClose(window)) {
        mainLoop();
    }
#endif

    // Tear down the system
    std::cout << "Loop ended" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

#else
#include "src/engine/renderer/Renderer.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"

using namespace DeepsEngine;

int main() {
    Renderer::getInstance().createWindow();
    Renderer::getInstance().initialize();

    // add camera entity
    Entity camera = Renderer::getInstance().scene.CreateEntity();
    (&camera.GetComponent<Component::Transform>())->position.z = 5.0;
    camera.AddComponent<Component::Camera>(Component::Camera({45.0f, 0.1f, 100.0f}));

    // add a single cube entity
    Entity entity = Renderer::getInstance().scene.CreateEntity();
    entity.AddComponent<Component::MeshFilter>(Component::MeshFilter{"cube"});

    while(!Renderer::getInstance().shouldCloseWindow()) {
        Renderer::getInstance().processInput();
        Renderer::getInstance().clear();
        Renderer::getInstance().update();
    }

    Renderer::getInstance().closeWindow();

    return 0;
}
#endif

#else

#include <QApplication>
#include "src/editor/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

#endif