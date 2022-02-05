#if defined(STANDALONE)

//#include <iostream>
//
//int main() {
//    std::cout << "hello world" << std::endl;
//}

#include "Engine/OpenGLRenderer.h"
#include "src/Engine/Renderer.h"

//int main() {
//    OpenGLRenderer::createWindow();
//    OpenGLRenderer::initialize();
//
//    // create a single entity for testing purposes
//    OpenGLRenderer::createEntity();
//
//    while (!OpenGLRenderer::shouldCloseWindow()) {
//        OpenGLRenderer::update();
//    }
//
//    OpenGLRenderer::closeWindow();
//
//    return 0;
//}

int main() {
    Renderer renderer;

    renderer.createWindow();
    renderer.initialize();

    while(!renderer.shouldCloseWindow()) {
        renderer.clear();
        renderer.update();
    }

    renderer.closeWindow();

    return 0;
}

#else

#include <QApplication>
#include "src/Editor/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

#endif