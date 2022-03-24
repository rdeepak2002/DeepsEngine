//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "InspectorWidget.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>

InspectorWidget::InspectorWidget(QWidget *parent) {
    // set max dimensions
    setMaximumWidth(300);
    setMinimumWidth(300.0);

    // title for this panel
    QLabel* panelTitle = new QLabel("Inspector");

    // tag widget
    tagComponentWidget = new TagComponentWidget;
    tagComponentWidget->setVisible(false);

    // transform widget
    transformComponentWidget = new TransformComponentWidget;
    transformComponentWidget->setVisible(false);

    // mesh filter widget
    meshFilterComponentWidget = new MeshFilterComponentWidget;
    meshFilterComponentWidget->setVisible(false);

    // drop down to add components
    addComponentButton = new QPushButton("Add Component");
    addComponentButton->setVisible(false);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(panelTitle);
    mainLayout->addWidget(tagComponentWidget);
    mainLayout->addWidget(transformComponentWidget);
    mainLayout->addWidget(meshFilterComponentWidget);
    mainLayout->addWidget(addComponentButton);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {
    delete tagComponentWidget;
    delete transformComponentWidget;
    delete meshFilterComponentWidget;
}

void InspectorWidget::onEntitySelected(DeepsEngine::Entity entity) {
    // define the entity selected pointer
    entitySelected.reset();
    entitySelected = std::make_shared<DeepsEngine::Entity>(entity);

    // make all widgets invisible again
    hideAllComponentWidgets();

    // refresh component view
    refresh();
}

void InspectorWidget::hideAllComponentWidgets() {
    // tag widget
    tagComponentWidget->setVisible(false);

    // transform widget
    transformComponentWidget->setVisible(false);

    // mesh filter widget
    meshFilterComponentWidget->setVisible(false);
}

void InspectorWidget::onAddComponentMenuClicked(QAction *action) {
    // get name of selected action from drop down menu
    std::string componentToAddName = action->text().toStdString();

    if (componentToAddName == "Tag") {
        // add tag component
        DeepsEngine::Component::Tag tag = {"entity"};
        entitySelected->AddComponent<DeepsEngine::Component::Tag>(tag);
    }
    else if(componentToAddName == "Transform") {
        // add transform component
        DeepsEngine::Component::Transform transform = {DeepsEngine::Component::Position({0, 0, 0}),
                                          DeepsEngine::Component::Rotation({0, 0, 0}),
                                          DeepsEngine::Component::Scale({1, 1, 1})};
        entitySelected->AddComponent<DeepsEngine::Component::Transform>(transform);
    }
    else if(componentToAddName == "Mesh Filter") {
        // add mesh filter component
        DeepsEngine::Component::MeshFilter cubeMeshFilter = {mesh: "cube"};
        entitySelected->AddComponent<DeepsEngine::Component::MeshFilter>(cubeMeshFilter);
    }

    refresh();
}

void InspectorWidget::refresh() {
    // show the necessary widgets
    if (entitySelected) {
        // menu for possible components to add
        addComponentButton->setVisible(true);
        // TODO: free memory of previous qmenu?
        QMenu* addComponentMenu = new QMenu;
        connect(addComponentMenu, SIGNAL(triggered(QAction*)), this, SLOT(onAddComponentMenuClicked(QAction*)));

        // show tag of entity
        if (entitySelected->HasComponent<DeepsEngine::Component::Tag>()) {
            tagComponentWidget->setVisible(true);
            DeepsEngine::Component::Tag* tagComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Tag>());
            tagComponentWidget->setTag(tagComponent);
        }
        else {
            addComponentMenu->addAction(tr("Tag"));
        }

        // show transform of entity
        if (entitySelected->HasComponent<DeepsEngine::Component::Transform>()) {
            transformComponentWidget->setVisible(true);
            DeepsEngine::Component::Transform* transformComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Transform>());
            transformComponentWidget->setTransform(transformComponent);
        }
        else {
            addComponentMenu->addAction(tr("Transform"));
        }

        // show mesh filter of entity
        if (entitySelected->HasComponent<DeepsEngine::Component::MeshFilter>()) {
            meshFilterComponentWidget->setVisible(true);
            DeepsEngine::Component::MeshFilter* meshFilterComponent = &(entitySelected->GetComponent<DeepsEngine::Component::MeshFilter>());
            meshFilterComponentWidget->setMeshFilter(meshFilterComponent);
        }
        else {
            addComponentMenu->addAction(tr("Mesh Filter"));
        }

        // update the menu of possible components to add
        addComponentButton->setMenu(addComponentMenu);

        // if no possible components to add, then do not display add component button
        if (addComponentMenu->isEmpty()) {
            addComponentButton->setVisible(false);
        }
    }
}
