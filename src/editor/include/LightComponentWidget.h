//
// Created by Deepak Ramalingam on 5/12/22.
//

#ifndef DEEPSENGINE_LIGHTCOMPONENTWIDGET_H
#define DEEPSENGINE_LIGHTCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class LightComponentWidget: public QWidget, ComponentWidget {
Q_OBJECT;
public:
    explicit LightComponentWidget(QWidget *parent = nullptr);
    ~LightComponentWidget();
private:
    void updateLightDropDownText();
    QPushButton* lightTypeBtn;

    QLineEdit* directionXInput;
    QLineEdit* directionYInput;
    QLineEdit* directionZInput;

    QLineEdit* ambientRInput;
    QLineEdit* ambientGInput;
    QLineEdit* ambientBInput;

    QLineEdit* diffuseRInput;
    QLineEdit* diffuseGInput;
    QLineEdit* diffuseBInput;

    QLineEdit* cutOffInput;
    QLineEdit* outerCutOffInput;

    DeepsEngine::Component::Light* lightComponent;

public slots:
    void setComponent(DeepsEngine::Component::Component* component) override;
    void onLightTypeMenuClicked(QAction* action);

    void onDirectionXInputChange();
    void onDirectionYInputChange();
    void onDirectionZInputChange();

    void onCutOffInputChange();
    void onOuterCutOffInputChange();

    void onAmbientRInputChange();
    void onAmbientGInputChange();
    void onAmbientBInputChange();

    void onDiffuseRInputChange();
    void onDiffuseGInputChange();
    void onDiffuseBInputChange();
};


#endif //DEEPSENGINE_LIGHTCOMPONENTWIDGET_H
