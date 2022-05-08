//
// Created by Deepak Ramalingam on 5/7/22.
//

#ifndef DEEPSENGINE_PROJECTWIDGET_H
#define DEEPSENGINE_PROJECTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "InspectorWidget.h"
#include "EntitySelectListenerInterface.h"

class ProjectWidget: public QWidget, EntitySelectListenerInterface {
Q_OBJECT;

public:
    explicit ProjectWidget(QWidget *parent = nullptr);
    ~ProjectWidget();
private:
    InspectorWidget* inspectorWidget;
public slots:
    void onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem) override;
};


#endif //DEEPSENGINE_PROJECTWIDGET_H
