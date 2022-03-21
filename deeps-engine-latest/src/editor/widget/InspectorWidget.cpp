//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "InspectorWidget.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>

InspectorWidget::InspectorWidget(QWidget *parent) {
    // set max dimensions
    setMaximumWidth(300);

    // create sample label
    entityTagComponentLabel = new QLabel("No entity selected");

    transformPositionXInput = new QLineEdit;
    transformPositionXInput->setValidator(new QDoubleValidator(-999999, 999999, 5, this));
    transformPositionXInput->setPlaceholderText("x");
    transformPositionXInput->setVisible(false);
    connect(transformPositionXInput, SIGNAL(textChanged(const QString &)), this, SLOT(onTransformPositionXInputChange()));
    // transformPositionXInput->setText(QString::fromStdString(std::to_string(entityTransformComponent->position.x)));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(entityTagComponentLabel);
    mainLayout->addWidget(transformPositionXInput);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {
    delete entityTagComponentLabel;
}

void InspectorWidget::onEntitySelected(DeepsEngine::Entity entity) {
    entitySelected.reset();
    entitySelected = std::make_shared<DeepsEngine::Entity>(entity);

    if (entitySelected) {
        // TODO: check hasComponent() for each possible component, then set the respective qt widget to *visible* for that
        // TODO: create widget class for each component type for special inputs for each (ex: transform component will store pointer to DeepsEngine::Component::Transform)
        // get name of entity
        DeepsEngine::Component::Tag entityTagComponent = entitySelected->GetComponent<DeepsEngine::Component::Tag>();
        entityTagComponentLabel->setText(QString::fromStdString(entityTagComponent.name));

        // get transform of entity
        transformPositionXInput->setVisible(true);
        DeepsEngine::Component::Transform* entityTransformComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Transform>());
        transformPositionXInput->setText(QString::fromStdString(std::to_string(entityTransformComponent->position.x)));
    }
}

void InspectorWidget::onTransformPositionXInputChange() {
    double newPositionX = transformPositionXInput->text().toDouble();

    DeepsEngine::Component::Transform* entityTransformComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Transform>());
    entityTransformComponent->position.x = newPositionX;
}
