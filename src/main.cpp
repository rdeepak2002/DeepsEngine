#include "Application.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>

extern "C" {
    void onResizeWindow(int width, int height) {
        Application::getInstance().resizeWindow(width, height);
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
    startUpdateLoop();
    Application::getInstance().close();

    return 0;
}

#else

#include <QApplication>
#include "src/editor/include/MainWindow.h"

int main(int argc, char *argv[])
{
    // set gl version
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    // launch qt application
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

#endif