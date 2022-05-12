//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_TRANSFORMCOMPONENTWIDGET_H
#define EDITOR_TRANSFORMCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class TransformComponentWidget: public QWidget, ComponentWidget {
Q_OBJECT;
public:
    explicit TransformComponentWidget(QWidget *parent = nullptr);
    ~TransformComponentWidget();
private:
    // reference to the transform being displayed
    DeepsEngine::Component::Transform* transformComponent;

    // position inputs
    QLineEdit* positionXInput;
    QLineEdit* positionYInput;
    QLineEdit* positionZInput;

    // rotation inputs
    QLineEdit* rotationXInput;
    QLineEdit* rotationYInput;
    QLineEdit* rotationZInput;

    // scale inputs
    QLineEdit* scaleXInput;
    QLineEdit* scaleYInput;
    QLineEdit* scaleZInput;

public slots:
    void setComponent(DeepsEngine::Component::Component* component) override;

    void onPositionXInputChange();
    void onPositionYInputChange();
    void onPositionZInputChange();

    void onRotationXInputChange();
    void onRotationYInputChange();
    void onRotationZInputChange();

    void onScaleXInputChange();
    void onScaleYInputChange();
    void onScaleZInputChange();
};


#endif //EDITOR_TRANSFORMCOMPONENTWIDGET_H
