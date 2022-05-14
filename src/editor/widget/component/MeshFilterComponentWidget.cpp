//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "MeshFilterComponentWidget.h"
#include "Component.h"
#include <iostream>
#include <QLabel>

MeshFilterComponentWidget::MeshFilterComponentWidget(QWidget *parent) {
    this->setVisible(false);

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

void MeshFilterComponentWidget::setComponent(DeepsEngine::Component::Component* component) {
    meshFilterComponent = dynamic_cast<DeepsEngine::Component::MeshFilter*>(component);

    if (meshFilterComponent) {
        meshFilterLabel->setText(QString::fromStdString(meshFilterComponent->mesh));
    }
}
