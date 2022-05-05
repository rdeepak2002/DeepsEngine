#ifndef mainwindow_h
#define mainwindow_h

#include <QtWidgets>
#include <QMainWindow>
#include <QScopedPointer>
#include "Entity.h"
#include "InspectorWidget.h"
#include "EntitySelectListenerInterface.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow, EntitySelectListenerInterface {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    InspectorWidget* inspectorWidget;

private:
    QScopedPointer<Ui::MainWindow> ui;

public slots:
    void onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem) override;
};

#endif
