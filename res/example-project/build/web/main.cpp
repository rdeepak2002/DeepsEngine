#include "Application.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#include "Input.h"

extern "C" {
    void onResizeWindow(int width, int height) {
        Application::getInstance().resizeWindow(width, height);
    }
    void onMouseMovement(double movementX, double movementY) {
        Input::SetMouseMovement(movementX, movementY);
    }
}
#endif

#if defined(STANDALONE)
void mainLoop() {
    Application::getInstance().update();
}

void startUpdateLoop() {
#ifdef EMSCRIPTEN
    // Define a mail loop function, that will be called as fast as possible
    emscripten_set_main_loop(&mainLoop, 0, 1);
#else
    // This is the normal C/C++ main loop
    while (!Application::getInstance().shouldClose()) {
        mainLoop();
    }
#endif
}

int main() {
    Application::getInstance().initialize();
#ifdef EMSCRIPTEN
    // create sample entities for web build
//    Application::getInstance().createSampleEntities();
#endif
    startUpdateLoop();
    Application::getInstance().close();

    return 0;
}

#else

#include <QApplication>
#include "ProjectWindow.h"

int main(int argc, char *argv[])
{
    // set gl version
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    // launch qt application
    QApplication app(argc, argv);
    ProjectWindow mainWindow;
//    mainWindow.show();
    return app.exec();
}

#endif