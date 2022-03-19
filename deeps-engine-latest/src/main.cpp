#if defined(STANDALONE)

#include "src/Engine/Renderer.h"

using namespace DeepsEngine;

int main() {
    Renderer::getInstance().createWindow();
    Renderer::getInstance().initialize();

    // create a scene with one entity
    auto* scene = new Scene();
    scene->createEntity();
    Renderer::getInstance().setScene(scene);

    while(!Renderer::getInstance().shouldCloseWindow()) {
        Renderer::getInstance().processInput();
        Renderer::getInstance().clear();
        Renderer::getInstance().update();
    }

    Renderer::getInstance().closeWindow();

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