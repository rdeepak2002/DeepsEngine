//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "MeshFilterComponentWidget.h"
#include "Component.h"
#include <iostream>
#include <QLabel>

MeshFilterComponentWidget::MeshFilterComponentWidget(QWidget *parent) {
    this->setVisible(false);

    fileSelectWidget = new FileSelectWidget(this, "All files (*.*);;obj (*.obj);;fbx (*.fbx)"); // All files (*.*);;
    connect(fileSelectWidget, SIGNAL(fileSelected(std::string, std::string)), this, SLOT(onFileSelected(std::string, std::string)));

    // create sample label
    meshFilterLabel = new QLabel("None");
    meshPathLabel = new QLabel("None");

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Mesh Filter"));
    mainLayout->addWidget(new QLabel("Type"));
    mainLayout->addWidget(meshFilterLabel);
    mainLayout->addWidget(new QLabel("Path"));
    mainLayout->addWidget(fileSelectWidget);
    setLayout(mainLayout);
}

MeshFilterComponentWidget::~MeshFilterComponentWidget() {
    delete meshFilterLabel;
    delete meshPathLabel;
}

void MeshFilterComponentWidget::setComponent(DeepsEngine::Component::Component* component) {
    meshFilterComponent = dynamic_cast<DeepsEngine::Component::MeshFilter*>(component);

    if (meshFilterComponent) {
        meshFilterLabel->setText(QString::fromStdString(meshFilterComponent->mesh));
        meshPathLabel->setText(QString::fromStdString(meshFilterComponent->meshPath));

        fileSelectWidget->setFilePath(meshFilterComponent->meshPath);
    }
}

void MeshFilterComponentWidget::onFileSelected(std::string relativeFilePath, std::string absoluteFilePath) {
    meshFilterComponent->setMeshPath(relativeFilePath);
}
