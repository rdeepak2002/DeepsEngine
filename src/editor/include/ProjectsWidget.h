//
// Created by Deepak Ramalingam on 5/7/22.
//

#ifndef DEEPSENGINE_PROJECTSWIDGET_H
#define DEEPSENGINE_PROJECTSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include "ProjectWindow.h"

class ProjectsWidget: public QWidget {
Q_OBJECT;

public:
    explicit ProjectsWidget(QWidget *parent = nullptr);
    ~ProjectsWidget();
    void closeEvent(QCloseEvent *event) override;
private:
    ProjectWindow* projectWindow;
    QMenu *fileMenu;
};


#endif //DEEPSENGINE_PROJECTSWIDGET_H
