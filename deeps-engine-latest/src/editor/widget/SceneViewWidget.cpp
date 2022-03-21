//
// Created by Deepak Ramalingam on 3/19/22.
//

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include "SceneViewWidget.h"
#include "src/engine/component/Component.h"
#include "src/engine/renderer/Renderer.h"
#include "src/engine/scene/Entity.h"
#include "src/editor/mainwindow.h"

SceneViewWidget::SceneViewWidget(QWidget *parent) {
    // set max dimensions
    setMaximumWidth(300);

    // start timer
    timerId = startTimer(500);

    // scene view list
    sceneViewList = new QListWidget;
    connect(sceneViewList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onListItemPressed(QListWidgetItem * )));

    // add entity button
    addButton = new QPushButton("Add", this);
    connect(addButton, SIGNAL(clicked()), this, SLOT(onAddButtonPressed()));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(sceneViewList);
    mainLayout->addWidget(addButton);
    setLayout(mainLayout);
}

SceneViewWidget::~SceneViewWidget() {
    killTimer(timerId);
}

void SceneViewWidget::timerEvent(QTimerEvent *event) {
    std::vector<DeepsEngine::Entity> newEntities = Renderer::getInstance().scene.GetEntities();

    if (newEntities.size() != entities.size()) {
        refreshSceneViewItems();
    }
}

void SceneViewWidget::refreshSceneViewItems() {
    sceneViewList->clear();
    entities = Renderer::getInstance().scene.GetEntities();

    for(auto entity : entities) {
        DeepsEngine::Component::Tag entityTag = entity.GetComponent<DeepsEngine::Component::Tag>();
        sceneViewList->addItem(QString::fromStdString(entityTag.name));
    }
}

void SceneViewWidget::onListItemPressed(QListWidgetItem* item) {
    // reference to main window
    auto *mainWindow = dynamic_cast<MainWindow *> (this->parentWidget()->parentWidget());

    if (mainWindow) {
        int rowIndex = sceneViewList->row(item);
        mainWindow->onEntitySelected(entities.at(rowIndex));
    }
    else {
        std::cout << "Error sending message from scene view to main window" << std::endl;
    }
}

void SceneViewWidget::onAddButtonPressed() {
    Renderer::getInstance().scene.CreateEntity("entity_" + std::to_string(entities.size()));
    refreshSceneViewItems();
}