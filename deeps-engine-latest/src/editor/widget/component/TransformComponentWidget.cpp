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
    positionXInput = new QLineEdit;
    positionXInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    positionXInput->setPlaceholderText("x");
    connect(positionXInput, SIGNAL(textChanged(const QString &)), this, SLOT(onPositionXInputChange()));

    // position y input
    positionYInput = new QLineEdit;
    positionYInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    positionYInput->setPlaceholderText("y");
    connect(positionYInput, SIGNAL(textChanged(const QString &)), this, SLOT(onPositionYInputChange()));

    // position z input
    positionZInput = new QLineEdit;
    positionZInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    positionZInput->setPlaceholderText("z");
    connect(positionZInput, SIGNAL(textChanged(const QString &)), this, SLOT(onPositionZInputChange()));

    // rotation x input
    rotationXInput = new QLineEdit;
    rotationXInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    rotationXInput->setPlaceholderText("x");
    connect(rotationXInput, SIGNAL(textChanged(const QString &)), this, SLOT(onRotationXInputChange()));

    // rotation y input
    rotationYInput = new QLineEdit;
    rotationYInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    rotationYInput->setPlaceholderText("y");
    connect(rotationYInput, SIGNAL(textChanged(const QString &)), this, SLOT(onRotationYInputChange()));

    // rotation z input
    rotationZInput = new QLineEdit;
    rotationZInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    rotationZInput->setPlaceholderText("z");
    connect(rotationZInput, SIGNAL(textChanged(const QString &)), this, SLOT(onRotationZInputChange()));

    // input fields for position
    QHBoxLayout* positionInputFieldsGroup = new QHBoxLayout;
    positionInputFieldsGroup->addWidget(new QLabel("x"));
    positionInputFieldsGroup->addWidget(positionXInput);
    positionInputFieldsGroup->addWidget(new QLabel("y"));
    positionInputFieldsGroup->addWidget(positionYInput);
    positionInputFieldsGroup->addWidget(new QLabel("z"));
    positionInputFieldsGroup->addWidget(positionZInput);

    // input fields for rotation
    QHBoxLayout* rotationInputFieldsGroup = new QHBoxLayout;
    rotationInputFieldsGroup->addWidget(new QLabel("x"));
    rotationInputFieldsGroup->addWidget(rotationXInput);
    rotationInputFieldsGroup->addWidget(new QLabel("y"));
    rotationInputFieldsGroup->addWidget(rotationYInput);
    rotationInputFieldsGroup->addWidget(new QLabel("z"));
    rotationInputFieldsGroup->addWidget(rotationZInput);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(componentTitle);
    mainLayout->addWidget(new QLabel("Position"));
    mainLayout->addLayout(positionInputFieldsGroup);
    mainLayout->addWidget(new QLabel("Rotation"));
    mainLayout->addLayout(rotationInputFieldsGroup);
    setLayout(mainLayout);
}

TransformComponentWidget::~TransformComponentWidget() {
    delete positionXInput;
    delete positionYInput;
    delete positionZInput;

    delete rotationXInput;
    delete rotationYInput;
    delete rotationZInput;
}

void TransformComponentWidget::setTransform(DeepsEngine::Component::Transform* transform) {
    transformComponent = transform;

    if (transformComponent) {
        positionXInput->setText(QString::fromStdString(std::to_string(transformComponent->position.x)));
        positionYInput->setText(QString::fromStdString(std::to_string(transformComponent->position.y)));
        positionZInput->setText(QString::fromStdString(std::to_string(transformComponent->position.z)));

        rotationXInput->setText(QString::fromStdString(std::to_string(transformComponent->rotation.x)));
        rotationYInput->setText(QString::fromStdString(std::to_string(transformComponent->rotation.y)));
        rotationZInput->setText(QString::fromStdString(std::to_string(transformComponent->rotation.z)));
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

void TransformComponentWidget::onRotationXInputChange() {
    transformComponent->rotation.x = rotationXInput->text().toFloat();
}

void TransformComponentWidget::onRotationYInputChange() {
    transformComponent->rotation.y = rotationYInput->text().toFloat();
}

void TransformComponentWidget::onRotationZInputChange() {
    transformComponent->rotation.z = rotationZInput->text().toFloat();
}
