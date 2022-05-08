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

class ProjectsWidget: public QWidget {
Q_OBJECT;

public:
    explicit ProjectsWidget(QWidget *parent = nullptr);
    ~ProjectsWidget();
};


#endif //DEEPSENGINE_PROJECTSWIDGET_H
