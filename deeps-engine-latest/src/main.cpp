#if !defined(STANDALONE)

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

#endif

#if defined(STANDALONE)

#include <iostream>

int main() {
    std::cout << "hello world" << std::endl;
}

//#include "OpenGLRenderer.h"
//
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

#endif