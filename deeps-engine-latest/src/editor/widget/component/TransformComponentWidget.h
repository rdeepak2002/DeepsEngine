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
    QLabel* componentTitle;
    QLineEdit* transformPositionXInput;
    DeepsEngine::Component::Transform* transformComponent;

public slots:
    void setTransform(DeepsEngine::Component::Transform* transform);
    void onPositionXInputChange();
};


#endif //EDITOR_TRANSFORMCOMPONENTWIDGET_H
