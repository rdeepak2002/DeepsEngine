//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "TransformComponentWidget.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>

TransformComponentWidget::TransformComponentWidget(QWidget *parent) {
    // create sample label
    componentTitle = new QLabel("Transform");

    // position x input
    transformPositionXInput = new QLineEdit;
    transformPositionXInput->setValidator(new QDoubleValidator(-999999, 999999, 5, this));
    transformPositionXInput->setPlaceholderText("x");
    connect(transformPositionXInput, SIGNAL(textChanged(const QString &)), this, SLOT(onPositionXInputChange()));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(componentTitle);
    mainLayout->addWidget(transformPositionXInput);
    setLayout(mainLayout);
}

TransformComponentWidget::~TransformComponentWidget() {
    delete componentTitle;
}

void TransformComponentWidget::setTransform(DeepsEngine::Component::Transform* transform) {
    transformComponent = transform;

    if (transformComponent) {
        transformPositionXInput->setText(QString::fromStdString(std::to_string(transformComponent->position.x)));
    }
}

void TransformComponentWidget::onPositionXInputChange() {
    double newPositionX = transformPositionXInput->text().toDouble();
    transformComponent->position.x = newPositionX;
}
