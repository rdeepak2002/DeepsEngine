//
// Created by Deepak Ramalingam on 3/19/22.
//

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include "SceneViewWidget.h"
#include "src/engine/header/Component.h"
#include "src/engine/header/Entity.h"
#include "src/engine/header/Application.h"

class MainWindow {
public:
    void onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem);
};

SceneViewWidget::SceneViewWidget(QWidget *parent) {
    // set max dimensions
    setMaximumWidth(300);
    setMinimumWidth(300.0);

    // start timer
    timerId = startTimer(500);

    // title for this panel
    QLabel* panelTitle = new QLabel("Scene");

    // scene view list
    sceneViewList = new QListWidget;
    connect(sceneViewList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onListItemPressed(QListWidgetItem * )));

    // add entity button
    addButton = new QPushButton("Add", this);
    connect(addButton, SIGNAL(clicked()), this, SLOT(onAddButtonPressed()));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(panelTitle);
    mainLayout->addWidget(sceneViewList);
    mainLayout->addWidget(addButton);
    setLayout(mainLayout);
}

SceneViewWidget::~SceneViewWidget() {
    killTimer(timerId);
}

void SceneViewWidget::timerEvent(QTimerEvent *event) {
    std::vector<DeepsEngine::Entity> newEntities = Application::getInstance().scene.GetEntities();

    if (newEntities.size() != entities.size()) {
        refreshSceneViewItems();
    }
}

void SceneViewWidget::refreshSceneViewItems() {
    sceneViewList->clear();
    entities = Application::getInstance().scene.GetEntities();

    for(auto entity : entities) {
        DeepsEngine::Component::Tag entityTag = entity.GetComponent<DeepsEngine::Component::Tag>();
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(entityTag.tag));
        sceneViewList->addItem(item);
        // TODO: how to deal with subchildren:
//        item->setSizeHint(QSize(0,65));
//        QListWidget *childrenList = new QListWidget;
//        childrenList->addItem("child 1");
//        childrenList->addItem("child 2");
//        childrenList->addItem("child 3");
//        sceneViewList->setItemWidget(item, childrenList);
    }
}

void SceneViewWidget::onListItemPressed(QListWidgetItem* item) {
    // reference to main window
    auto *mainWindow = dynamic_cast<MainWindow *> (this->parentWidget()->parentWidget());

    if (mainWindow) {
        int rowIndex = sceneViewList->row(item);
        mainWindow->onEntitySelected(entities.at(rowIndex), sceneViewList->currentItem());
    }
    else {
        Logger::Debug("Error sending message from scene view to main window");
    }
}

void SceneViewWidget::onAddButtonPressed() {
    Application::getInstance().scene.CreateEntity("Entity " + std::to_string(entities.size() + 1));
}