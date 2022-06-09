#include "Application.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>

extern "C" {
    void onResizeWindow(int width, int height) {
        Application::getInstance().resizeWindow(width, height);
    }
}
#endif

#include <dlfcn.h>
#include <stdio.h>

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
    void *handle;
    void (*func_print_name)(const char*);

    handle = dlopen("/Users/deepakramalingam/Desktop/native/cmake-build-debug/libnative.dylib", RTLD_LAZY);

    if (!handle) {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    *(void**)(&func_print_name) = dlsym(handle, "print_name");

    if (!func_print_name) {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return EXIT_FAILURE;
    }

    func_print_name("test");
    dlclose(handle);

    return EXIT_SUCCESS;

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