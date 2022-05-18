//
// Created by Deepak Ramalingam on 3/19/22.
//

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "SceneViewWidget.h"
#include "Component.h"
#include "Entity.h"
#include "Application.h"

SceneViewWidget::SceneViewWidget(QWidget *parent) {
    // set max dimensions
    setMaximumWidth(300);
    setMinimumWidth(300.0);

    // start timer
    timerId = startTimer(500);

    // title for this panel
    QLabel* panelTitle = new QLabel("Scene");

    // scene view tree
    treeWidget = new QTreeWidget;
    connect(treeWidget, &QTreeWidget::itemClicked, this, &SceneViewWidget::onListItemPressed);
    connect(treeWidget->selectionModel(), SIGNAL( selectionChanged( const QItemSelection &, const QItemSelection & )), this, SLOT( selectionChanged( const QItemSelection &, const QItemSelection & ) ));

    // map of items to entities
    entityItemMap = new QHash<QTreeWidgetItem*, std::shared_ptr<DeepsEngine::Entity>>;

    // scene view list
//    sceneViewList = new QListWidget;
//    sceneViewList->setStyleSheet(sceneViewList->styleSheet().append("background-color: transparent;"));
//    connect(sceneViewList, SIGNAL(itemClicked(QListWidgetItem*)),
//            this, SLOT(onListItemPressed(QListWidgetItem * )));

    // add entity button
    addButton = new QPushButton("Add", this);
    connect(addButton, SIGNAL(clicked()), this, SLOT(onAddButtonPressed()));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(panelTitle);
//    mainLayout->addWidget(sceneViewList);
    mainLayout->addWidget(treeWidget);
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
    treeWidget->clear();
    entities = Application::getInstance().scene.GetEntities();

    for(auto entity : entities) {
        // only show list items that are the root
        if (entity.HasComponent<DeepsEngine::Component::HierarchyComponent>()) {
            if (entity.GetComponent<DeepsEngine::Component::HierarchyComponent>().parentGuid != "root") {
                continue;
            }
        }

        DeepsEngine::Component::Tag entityTag = entity.GetComponent<DeepsEngine::Component::Tag>();
        QTreeWidgetItem* treeItem = new QTreeWidgetItem(treeWidget);
        treeItem->setText(0, QString::fromStdString(entityTag.tag));
        entityItemMap->insert(treeItem, std::make_shared<DeepsEngine::Entity>(entity));

        // add children entities
        addChildTreeItems(std::make_shared<DeepsEngine::Entity>(entity), treeItem);
    }
}

void SceneViewWidget::addChildTreeItems(std::shared_ptr<DeepsEngine::Entity> entity, QTreeWidgetItem* treeItem) {
    if (entity->HasComponent<DeepsEngine::Component::HierarchyComponent>()) {
        for (std::string childEntityGuid : entity->GetComponent<DeepsEngine::Component::HierarchyComponent>().childrenGuids) {
            std::shared_ptr<DeepsEngine::Entity> childEntity = std::make_shared<DeepsEngine::Entity>(*Application::getInstance().scene.findEntityByGuid(childEntityGuid));

            if (childEntity) {
                auto* treeItemChild = new QTreeWidgetItem();
                DeepsEngine::Component::Tag entityTag = childEntity->GetComponent<DeepsEngine::Component::Tag>();
                treeItemChild->setText(0, QString::fromStdString(entityTag.tag));
                treeItem->addChild(treeItemChild);
                entityItemMap->insert(treeItemChild, childEntity);

                addChildTreeItems(childEntity, treeItemChild);
            }
        }
    }
}

void SceneViewWidget::onListItemPressed(QTreeWidgetItem* item, int column) {
    if (entitySelectListenerInterface) {
        entitySelectListenerInterface->onEntitySelected(entityItemMap, treeWidget->currentItem());
    } else {
        Logger::Error("Entity select listener not defined in SceneViewWidget");
    }
}

void SceneViewWidget::onAddButtonPressed() {
    DeepsEngine::Entity newEntity = Application::getInstance().scene.CreateEntity("Entity " + std::to_string(entities.size() + 1));

    // check if entity is selected, then make this new entity a child of the selected one
    QTreeWidgetItem* currentlySelectedItem = treeWidget->currentItem();

    if (currentlySelectedItem) {
        std::shared_ptr<DeepsEngine::Entity> selectedEntity = entityItemMap->value(currentlySelectedItem);
        selectedEntity->GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(newEntity);
    }
}

void SceneViewWidget::setEntitySelectListener(EntitySelectListenerInterface *entitySelectListenerInterface) {
    this->entitySelectListenerInterface = entitySelectListenerInterface;
}

void SceneViewWidget::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == 16777216 || event->key() == Qt::Key::Key_Escape) {
        treeWidget->clearSelection();
        treeWidget->setCurrentItem(nullptr);
    }
}
