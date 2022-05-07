#ifndef mainwindow_h
#define mainwindow_h

#include <QtWidgets>
#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QObject>
#include "Entity.h"
#include "InspectorWidget.h"
#include "EntitySelectListenerInterface.h"
#include <QString>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>

class MainWindow : public QMainWindow, EntitySelectListenerInterface {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    InspectorWidget* inspectorWidget;

public slots:
    void onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem) override;
    void buildWeb();
};

#endif
