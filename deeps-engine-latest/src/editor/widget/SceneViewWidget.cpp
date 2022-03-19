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
    // scene view
    QListWidget *sceneViewScrollArea = new QListWidget;
    sceneViewScrollArea->addItem("test 1");

    // TODO: the crashing is due to the ".scene" call
    // TODO: maybe dont make scene variable a pointer?
    std::cout << "number of entities for scene view: " << Renderer::getInstance().scene.GetEntities().size() << std::endl;

    for(auto entity : Renderer::getInstance().scene.GetEntities()) {
        DeepsEngine::Component::Tag entityTag = entity.GetComponent<DeepsEngine::Component::Tag>();
        sceneViewScrollArea->addItem(QString::fromStdString(entityTag.name));
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(sceneViewScrollArea, 0, 0);

    setLayout(mainLayout);
}

SceneViewWidget::~SceneViewWidget() {

}
