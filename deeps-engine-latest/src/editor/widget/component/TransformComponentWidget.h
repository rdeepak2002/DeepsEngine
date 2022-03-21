//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_TRANSFORMCOMPONENTWIDGET_H
#define EDITOR_TRANSFORMCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"

class TransformComponentWidget: public QWidget {
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

public slots:
    void setTransform(DeepsEngine::Component::Transform* transform);
    void onPositionXInputChange();
    void onPositionYInputChange();
    void onPositionZInputChange();
};


#endif //EDITOR_TRANSFORMCOMPONENTWIDGET_H
