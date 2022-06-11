#include "Application.h"
#include "library.h"

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
    // load the triangle library
    void* triangle = dlopen("/Users/deepakramalingam/Desktop/native/cmake-build-debug/libnative.dylib", RTLD_LAZY);
    if (!triangle) {
        cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // reset errors
    dlerror();

    // load the symbols
    create_t* create_triangle = (create_t*) dlsym(triangle, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return 1;
    }

    destroy_t* destroy_triangle = (destroy_t*) dlsym(triangle, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
        return 1;
    }

    // create an instance of the class
    polygon* poly = create_triangle();

    // use the class
    poly->set_side_length(7);
    cout << "The area is: " << poly->area() << '\n';

    // destroy the class
    destroy_triangle(poly);

    // unload the triangle library
    dlclose(triangle);

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