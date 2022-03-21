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
    inspectorTitle = new QLabel("Inspector");

    // tag widget
    tagComponentWidget = new TagComponentWidget;
    tagComponentWidget->setVisible(false);

    // transform widget
    transformComponentWidget = new TransformComponentWidget;
    transformComponentWidget->setVisible(false);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(inspectorTitle);
    mainLayout->addWidget(tagComponentWidget);
    mainLayout->addWidget(transformComponentWidget);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {
    delete inspectorTitle;
    delete transformComponentWidget;
}

void InspectorWidget::onEntitySelected(DeepsEngine::Entity entity) {
    // define the entity selected pointer
    entitySelected.reset();
    entitySelected = std::make_shared<DeepsEngine::Entity>(entity);

    // make all widgets invisible again
    hideAllComponentWidgets();

    // show the necessary widgets
    if (entitySelected) {
        // show tag of entity
        if (entity.HasComponent<DeepsEngine::Component::Tag>()) {
            tagComponentWidget->setVisible(true);
            DeepsEngine::Component::Tag* tagComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Tag>());
            tagComponentWidget->setTag(tagComponent);
        }

        // show transform of entity
        if (entity.HasComponent<DeepsEngine::Component::Transform>()) {
            transformComponentWidget->setVisible(true);
            DeepsEngine::Component::Transform* transformComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Transform>());
            transformComponentWidget->setTransform(transformComponent);
        }
    }
}

void InspectorWidget::hideAllComponentWidgets() {
    // tag widget
    tagComponentWidget->setVisible(false);

    // transform widget
    transformComponentWidget->setVisible(false);
}
