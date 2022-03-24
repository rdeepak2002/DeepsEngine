//
// Created by Deepak Ramalingam on 3/24/22.
//

#include "CameraComponentWidget.h"

#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>

CameraComponentWidget::CameraComponentWidget(QWidget *parent) {
    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Camera"));
    setLayout(mainLayout);
}

CameraComponentWidget::~CameraComponentWidget() {

}

void CameraComponentWidget::setCamera(DeepsEngine::Component::Camera* camera) {
    cameraComponent = camera;

    if (cameraComponent) {
        // TODO: add fov, znear, zfar, etc.
    }
}
