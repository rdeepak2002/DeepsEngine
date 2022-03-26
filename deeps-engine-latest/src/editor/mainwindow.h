#ifndef mainwindow_h
#define mainwindow_h

#include <QtWidgets>
#include <QMainWindow>
#include <QScopedPointer>
#include "src/engine/scene/Entity.h"
#include "src/editor/widget/InspectorWidget.h"
#include "src/editor/widget/SceneViewWidget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    SceneViewWidget* sceneViewWidget;
    InspectorWidget* inspectorWidget;

private:
    QScopedPointer<Ui::MainWindow> ui;

public slots:
    void onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem);
};

#endif
