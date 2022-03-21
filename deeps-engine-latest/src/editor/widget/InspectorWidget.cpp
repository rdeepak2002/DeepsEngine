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

    // transform widget
    transformComponentWidget = new TransformComponentWidget;
    transformComponentWidget->setVisible(false);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(entityTagComponentLabel);
    mainLayout->addWidget(transformComponentWidget);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {
    delete entityTagComponentLabel;
    delete transformComponentWidget;
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

        // show transform of entity
        if (entity.HasComponent<DeepsEngine::Component::Transform>()) {
            transformComponentWidget->setVisible(true);
            DeepsEngine::Component::Transform* entityTransformComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Transform>());
            transformComponentWidget->setTransform(entityTransformComponent);
        }
    }
}