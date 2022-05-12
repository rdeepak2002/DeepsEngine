//
// Created by Deepak Ramalingam on 5/12/22.
//

#ifndef DEEPSENGINE_LIGHTCOMPONENTWIDGET_H
#define DEEPSENGINE_LIGHTCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class LightComponentWidget: public QWidget, ComponentWidget {
Q_OBJECT;
public:
    explicit LightComponentWidget(QWidget *parent = nullptr);
    ~LightComponentWidget();
private:
    QLabel* lightLabel;
    DeepsEngine::Component::Light* lightComponent;

public slots:
    void setComponent(DeepsEngine::Component::Component* component) override;
};


#endif //DEEPSENGINE_LIGHTCOMPONENTWIDGET_H
