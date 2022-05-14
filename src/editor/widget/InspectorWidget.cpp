//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "InspectorWidget.h"
#include "Entity.h"
#include "Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>

InspectorWidget::InspectorWidget(QWidget *parent) {
    // title for this panel
    QLabel* panelTitle = new QLabel("Inspector");

    // TODO: make all these component widgets extend a common class so you can just iterate through vector for this

    // tag widget
    tagComponentWidget = new TagComponentWidget(this);
    tagComponentWidget->setVisible(false);

    // transform widget
    transformComponentWidget = new TransformComponentWidget;
    transformComponentWidget->setVisible(false);

    // camera widget
    cameraComponentWidget = new CameraComponentWidget;
    cameraComponentWidget->setVisible(false);

    // mesh filter widget
    meshFilterComponentWidget = new MeshFilterComponentWidget;
    meshFilterComponentWidget->setVisible(false);

    // light widget
    lightComponentWidget = new LightComponentWidget;
    lightComponentWidget->setVisible(false);

    // drop down to add components
    addComponentButton = new QPushButton("Add Component");
    addComponentButton->setVisible(false);

    // remove entity button
    removeEntityButton = new QPushButton("Remove Entity", this);
    removeEntityButton->setVisible(false);
    connect(removeEntityButton, SIGNAL(clicked()), this, SLOT(onRemoveEntityButtonClicked()));

    // add component widgets to be iterated through
    componentWidgets.append(tagComponentWidget);
    componentWidgets.append(transformComponentWidget);
    componentWidgets.append(cameraComponentWidget);
    componentWidgets.append(meshFilterComponentWidget);
    componentWidgets.append(lightComponentWidget);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(panelTitle);
    for (ComponentWidget* componentWidget : componentWidgets) {
        mainLayout->addWidget(componentWidget);
    }
    mainLayout->addWidget(addComponentButton);
    mainLayout->addWidget(removeEntityButton);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {
    for (ComponentWidget* componentWidget : componentWidgets) {
        delete componentWidget;
    }
}

void InspectorWidget::onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem) {
    // reference to list view object
    this->listItem = listItem;

    // define the entity selected pointer
    entitySelected.reset();
    entitySelected = std::make_shared<DeepsEngine::Entity>(entity);

    // make all widgets invisible again
    hideAllComponentWidgets();

    // refresh component view
    refresh();
}

void InspectorWidget::hideAllComponentWidgets() {
    // hide all component widgets
    for (ComponentWidget* componentWidget : componentWidgets) {
        componentWidget->setVisible(false);
    }
}

void InspectorWidget::onAddComponentMenuClicked(QAction *action) {
    // get name of selected action from drop down menu
    std::string componentToAddName = action->text().toStdString();

    // add the component
    for (ComponentWidget* componentWidget : componentWidgets) {
        if (componentToAddName == componentWidget->getName()) {
            componentWidget->addComponentToEntity(entitySelected);
        }
    }

    refresh();
}

void InspectorWidget::refresh() {
    // show the necessary widgets
    if (entitySelected) {
        // menu for possible components to add
        addComponentButton->setVisible(true);

        // button to remove entity
        removeEntityButton->setVisible(true);

        // TODO: free memory of previous qmenu?
        QMenu* addComponentMenu = new QMenu;
        connect(addComponentMenu, SIGNAL(triggered(QAction*)), this, SLOT(onAddComponentMenuClicked(QAction*)));

        // allow each component widget to refer to the entity's component and if it is not found, append its name to the menu
        for (ComponentWidget* componentWidget : componentWidgets) {
            if (!componentWidget->getComponentFromEntity(entitySelected)) {
                addComponentMenu->addAction(tr(componentWidget->getName().c_str()));
            }
        }

        // update the menu of possible components to add
        addComponentButton->setMenu(addComponentMenu);

        // if no possible components to add, then do not display add component button
        if (addComponentMenu->isEmpty()) {
            addComponentButton->setVisible(false);
        }
    }
    else {
        hideAllComponentWidgets();
    }
}

void InspectorWidget::onRemoveEntityButtonClicked() {
    if (this->entitySelected) {
        this->entitySelected->Destroy();
        this->entitySelected.reset();
        this->refresh();
    }
}
