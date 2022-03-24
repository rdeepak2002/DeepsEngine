//
// Created by Deepak Ramalingam on 3/24/22.
//

#ifndef EDITOR_CAMERACOMPONENTWIDGET_H
#define EDITOR_CAMERACOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"

class CameraComponentWidget: public QWidget {
    Q_OBJECT;
public:
    explicit CameraComponentWidget(QWidget *parent = nullptr);
    ~CameraComponentWidget();
private:
    DeepsEngine::Component::Camera* cameraComponent;

public slots:
    void setCamera(DeepsEngine::Component::Camera* camera);
};




#endif //EDITOR_CAMERACOMPONENTWIDGET_H
