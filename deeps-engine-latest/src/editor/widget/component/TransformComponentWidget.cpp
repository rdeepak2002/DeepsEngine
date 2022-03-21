//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "TransformComponentWidget.h"
#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>

TransformComponentWidget::TransformComponentWidget(QWidget *parent) {
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

    // scale x input
    scaleXInput = new QLineEdit;
    scaleXInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    scaleXInput->setPlaceholderText("x");
    connect(scaleXInput, SIGNAL(textChanged(const QString &)), this, SLOT(onScaleXInputChange()));

    // scale y input
    scaleYInput = new QLineEdit;
    scaleYInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    scaleYInput->setPlaceholderText("y");
    connect(scaleYInput, SIGNAL(textChanged(const QString &)), this, SLOT(onScaleYInputChange()));

    // scale z input
    scaleZInput = new QLineEdit;
    scaleZInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    scaleZInput->setPlaceholderText("z");
    connect(scaleZInput, SIGNAL(textChanged(const QString &)), this, SLOT(onScaleZInputChange()));

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

    // input fields for scale
    QHBoxLayout* scaleInputFieldsGroup = new QHBoxLayout;
    scaleInputFieldsGroup->addWidget(new QLabel("x"));
    scaleInputFieldsGroup->addWidget(scaleXInput);
    scaleInputFieldsGroup->addWidget(new QLabel("y"));
    scaleInputFieldsGroup->addWidget(scaleYInput);
    scaleInputFieldsGroup->addWidget(new QLabel("z"));
    scaleInputFieldsGroup->addWidget(scaleZInput);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Transform"));
    mainLayout->addWidget(new QLabel("Position"));
    mainLayout->addLayout(positionInputFieldsGroup);
    mainLayout->addWidget(new QLabel("Rotation"));
    mainLayout->addLayout(rotationInputFieldsGroup);
    mainLayout->addWidget(new QLabel("Scale"));
    mainLayout->addLayout(scaleInputFieldsGroup);
    setLayout(mainLayout);
}

TransformComponentWidget::~TransformComponentWidget() {
    delete positionXInput;
    delete positionYInput;
    delete positionZInput;

    delete rotationXInput;
    delete rotationYInput;
    delete rotationZInput;

    delete scaleXInput;
    delete scaleYInput;
    delete scaleZInput;
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

        scaleXInput->setText(QString::fromStdString(std::to_string(transformComponent->scale.x)));
        scaleYInput->setText(QString::fromStdString(std::to_string(transformComponent->scale.y)));
        scaleZInput->setText(QString::fromStdString(std::to_string(transformComponent->scale.z)));
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

void TransformComponentWidget::onScaleXInputChange() {
    transformComponent->scale.x = scaleXInput->text().toFloat();
}

void TransformComponentWidget::onScaleYInputChange() {
    transformComponent->scale.y = scaleYInput->text().toFloat();
}

void TransformComponentWidget::onScaleZInputChange() {
    transformComponent->scale.z = scaleZInput->text().toFloat();
}
