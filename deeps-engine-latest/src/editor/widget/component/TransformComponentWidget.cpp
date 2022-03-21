//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "TransformComponentWidget.h"
#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>

TransformComponentWidget::TransformComponentWidget(QWidget *parent) {
    // create sample label
    QLabel* componentTitle = new QLabel("Transform");

    // position x input
    QLabel* positionXLabel = new QLabel("x: ");
    positionXInput = new QLineEdit;
    positionXInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    positionXInput->setPlaceholderText("x");
    connect(positionXInput, SIGNAL(textChanged(const QString &)), this, SLOT(onPositionXInputChange()));

    // position y input
    QLabel* positionYLabel = new QLabel("y: ");
    positionYInput = new QLineEdit;
    positionYInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    positionYInput->setPlaceholderText("y");
    connect(positionYInput, SIGNAL(textChanged(const QString &)), this, SLOT(onPositionYInputChange()));

    // position z input
    QLabel* positionZLabel = new QLabel("z: ");
    positionZInput = new QLineEdit;
    positionZInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    positionZInput->setPlaceholderText("z");
    connect(positionZInput, SIGNAL(textChanged(const QString &)), this, SLOT(onPositionZInputChange()));

    // input fields for position
    QHBoxLayout* positionInputFieldsGroup = new QHBoxLayout;
    positionInputFieldsGroup->addWidget(positionXLabel);
    positionInputFieldsGroup->addWidget(positionXInput);
    positionInputFieldsGroup->addWidget(positionYLabel);
    positionInputFieldsGroup->addWidget(positionYInput);
    positionInputFieldsGroup->addWidget(positionZLabel);
    positionInputFieldsGroup->addWidget(positionZInput);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(componentTitle);
    mainLayout->addWidget(new QLabel("Position"));
    mainLayout->addLayout(positionInputFieldsGroup);
    setLayout(mainLayout);
}

TransformComponentWidget::~TransformComponentWidget() {
    delete positionXInput;
    delete positionYInput;
    delete positionZInput;
}

void TransformComponentWidget::setTransform(DeepsEngine::Component::Transform* transform) {
    transformComponent = transform;

    if (transformComponent) {
        positionXInput->setText(QString::fromStdString(std::to_string(transformComponent->position.x)));
        positionYInput->setText(QString::fromStdString(std::to_string(transformComponent->position.y)));
        positionZInput->setText(QString::fromStdString(std::to_string(transformComponent->position.z)));
    }
}

void TransformComponentWidget::onPositionXInputChange() {
    transformComponent->position.x = positionXInput->text().toFloat();
}

void TransformComponentWidget::onPositionYInputChange() {
    transformComponent->position.y = positionYInput->text().toFloat();
}

void TransformComponentWidget::onPositionZInputChange() {
    transformComponent->position.z = positionZInput->text().toFloat();
}
