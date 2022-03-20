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

SceneViewWidget::SceneViewWidget(QWidget *parent) {
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
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(sceneViewList, 0, 0);
    mainLayout->addWidget(addButton, 1, 0);
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
    std::vector<DeepsEngine::Entity> newEntities = Renderer::getInstance().scene.GetEntities();

    std::cout << "updating scene view list" << std::endl;

    sceneViewList->clear();

    entities = newEntities;

    for(auto entity : entities) {
        DeepsEngine::Component::Tag entityTag = entity.GetComponent<DeepsEngine::Component::Tag>();
        sceneViewList->addItem(QString::fromStdString(entityTag.name));
    }
}

void SceneViewWidget::onListItemPressed(QListWidgetItem* item) {
    std::cout << "clicked on item in row: " << sceneViewList->row(item) << std::endl;
}

void SceneViewWidget::onAddButtonPressed() {
    Renderer::getInstance().scene.CreateEntity();
    refreshSceneViewItems();
}