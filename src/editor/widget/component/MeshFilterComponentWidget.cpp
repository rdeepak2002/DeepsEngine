//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "MeshFilterComponentWidget.h"
#include "src/engine/header/Component.h"
#include <iostream>
#include <QLabel>

MeshFilterComponentWidget::MeshFilterComponentWidget(QWidget *parent) {
    // create sample label
    meshFilterLabel = new QLabel("None");

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Mesh Filter"));
    mainLayout->addWidget(meshFilterLabel);
    setLayout(mainLayout);
}

MeshFilterComponentWidget::~MeshFilterComponentWidget() {
    delete meshFilterLabel;
}

void MeshFilterComponentWidget::setMeshFilter(DeepsEngine::Component::MeshFilter* meshFilter) {
    meshFilterComponent = meshFilter;

    if (meshFilterComponent) {
        meshFilterLabel->setText(QString::fromStdString(meshFilter->mesh));
    }
}
