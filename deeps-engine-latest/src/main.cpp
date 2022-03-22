#if defined(STANDALONE)

#include "src/engine/renderer/Renderer.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"

using namespace DeepsEngine;

int main() {
    Renderer::getInstance().createWindow();
    Renderer::getInstance().initialize();

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