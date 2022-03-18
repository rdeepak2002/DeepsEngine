#if defined(STANDALONE)

#include "src/Engine/Renderer.h"

int main() {
    Renderer renderer;

    renderer.createWindow();
    renderer.initialize();

    while(!renderer.shouldCloseWindow()) {
        renderer.processInput();
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