//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "InspectorWidget.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>

InspectorWidget::InspectorWidget(QWidget *parent) {
    // set max dimensions
    setMaximumWidth(300);

    // create sample label
    entityTagComponentLabel = new QLabel("");

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(entityTagComponentLabel);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {
    delete entityTagComponentLabel;
}

void InspectorWidget::onEntitySelected(DeepsEngine::Entity entity) {
    entitySelected.reset();
    entitySelected = std::make_shared<DeepsEngine::Entity>(entity);

    if (entitySelected) {
        DeepsEngine::Component::Tag entityTagComponent = entitySelected->GetComponent<DeepsEngine::Component::Tag>();
        // TODO: use unique smart pointer for updating components
        DeepsEngine::Component::Transform* entityTransformComponent = &entitySelected->GetComponent<DeepsEngine::Component::Transform>();
        entityTransformComponent->position.x = 2.0;
        entityTagComponentLabel->setText(QString::fromStdString(entityTagComponent.name));
    }
}