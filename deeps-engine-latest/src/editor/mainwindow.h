#ifndef mainwindow_h
#define mainwindow_h

#include <QtWidgets>
#include <QMainWindow>
#include <QScopedPointer>
#include "src/engine/scene/Entity.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    int testVar = 2;

private:
    QScopedPointer<Ui::MainWindow> ui;

public slots:
    void onEntitySelected(DeepsEngine::Entity entity);
};

#endif
