//
// Created by Deepak Ramalingam on 3/24/22.
//

#include "CameraComponentWidget.h"

#include "Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>

CameraComponentWidget::CameraComponentWidget(QWidget *parent) {
    // fov input
    fovInput = new QLineEdit;
    fovInput->setValidator(new QDoubleValidator(-360, 360, 3, this));
    fovInput->setPlaceholderText("fov");
    connect(fovInput, SIGNAL(textChanged(const QString &)), this, SLOT(onFovInputChange()));

    // zNear input
    zNearInput = new QLineEdit;
    zNearInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    zNearInput->setPlaceholderText("zNear");
    connect(zNearInput, SIGNAL(textChanged(const QString &)), this, SLOT(onZNearInputChange()));

    // zFar input
    zFarInput = new QLineEdit;
    zFarInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    zFarInput->setPlaceholderText("zFar");
    connect(zFarInput, SIGNAL(textChanged(const QString &)), this, SLOT(onZFarInputChange()));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Camera"));
    mainLayout->addWidget(new QLabel("FOV"));
    mainLayout->addWidget(fovInput);
    mainLayout->addWidget(new QLabel("zNear"));
    mainLayout->addWidget(zNearInput);
    mainLayout->addWidget(new QLabel("zFar"));
    mainLayout->addWidget(zFarInput);
    setLayout(mainLayout);
}

CameraComponentWidget::~CameraComponentWidget() {

}

void CameraComponentWidget::setComponent(DeepsEngine::Component::Component* component) {
    cameraComponent = dynamic_cast<DeepsEngine::Component::Camera*>(component);

    if (cameraComponent) {
        fovInput->setText(QString::fromStdString(std::to_string(cameraComponent->fov)));
        zNearInput->setText(QString::fromStdString(std::to_string(cameraComponent->zNear)));
        zFarInput->setText(QString::fromStdString(std::to_string(cameraComponent->zFar)));
    }
}

void CameraComponentWidget::onFovInputChange() {
    cameraComponent->fov = fovInput->text().toFloat();
}

void CameraComponentWidget::onZNearInputChange() {
    cameraComponent->zNear = zNearInput->text().toFloat();
}

void CameraComponentWidget::onZFarInputChange() {
    cameraComponent->zFar = zFarInput->text().toFloat();
}

