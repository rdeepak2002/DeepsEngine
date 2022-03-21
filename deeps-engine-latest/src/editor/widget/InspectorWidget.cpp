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
    mainLayout->addWidget(entityTagComponentLabel);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {
    delete entityTagComponentLabel;
}

void InspectorWidget::onEntitySelected(DeepsEngine::Entity entity) {
    entitySelected = &entity;

    if (entitySelected) {
        DeepsEngine::Component::Tag entityTag = entitySelected->GetComponent<DeepsEngine::Component::Tag>();
        entityTagComponentLabel->setText(QString::fromStdString(entityTag.name));
    }
}