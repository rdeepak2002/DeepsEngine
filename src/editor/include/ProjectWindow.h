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

class ProjectWindow : public QMainWindow {
    Q_OBJECT;

public:
    ProjectWindow(QWidget *parent = 0);
    virtual ~ProjectWindow();

public slots:
    void showProjectWindow();
    void showProjectsWindow();
    void buildWeb();
    void updateBuilds();
};

#endif
