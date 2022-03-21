//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "InspectorWidget.h"
#include <iostream>
#include <QLabel>

InspectorWidget::InspectorWidget(QWidget *parent) {
    // set max dimensions
    setMaximumWidth(300);

    // create sample label
    QLabel* testLabel = new QLabel("test label");

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(testLabel);
    setLayout(mainLayout);
}

InspectorWidget::~InspectorWidget() {

}

void InspectorWidget::onSceneViewItemSelected(QListWidgetItem* item) {
    std::cout << "item got" << std::endl;
//    std::cout << "clicked on item in row: " << sceneViewList->row(item) << std::endl;
}