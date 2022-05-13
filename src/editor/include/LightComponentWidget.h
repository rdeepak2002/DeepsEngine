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
    void hideAllLightConfigOptions();
    void showNecessaryLightConfigOptions();

    // field groups to easily make visible and invisible
    QWidget* lightTypeGroup;
    QWidget* cutOffGroup;
    QWidget* outerCutOffGroup;
    QWidget* ambientGroup;
    QWidget* diffuseGroup;
    QWidget* specularGroup;
    QWidget* constantGroup;
    QWidget* linearGroup;
    QWidget* quadraticGroup;

    QPushButton* lightTypeBtn;

    QLineEdit* ambientRInput;
    QLineEdit* ambientGInput;
    QLineEdit* ambientBInput;

    QLineEdit* diffuseRInput;
    QLineEdit* diffuseGInput;
    QLineEdit* diffuseBInput;

    QLineEdit* specularRInput;
    QLineEdit* specularGInput;
    QLineEdit* specularBInput;

    QLineEdit* cutOffInput;
    QLineEdit* outerCutOffInput;

    QLineEdit* constantInput;
    QLineEdit* linearInput;
    QLineEdit* quadraticInput;

    DeepsEngine::Component::Light* lightComponent;

public slots:
    void setComponent(DeepsEngine::Component::Component* component) override;
    void onLightTypeMenuClicked(QAction* action);

    void onCutOffInputChange();
    void onOuterCutOffInputChange();

    void onAmbientRInputChange();
    void onAmbientGInputChange();
    void onAmbientBInputChange();

    void onDiffuseRInputChange();
    void onDiffuseGInputChange();
    void onDiffuseBInputChange();

    void onSpecularRInputChange();
    void onSpecularGInputChange();
    void onSpecularBInputChange();

    void onConstantInputChange();
    void onLinearInputChange();
    void onQuadraticInputChange();
};


#endif //DEEPSENGINE_LIGHTCOMPONENTWIDGET_H
