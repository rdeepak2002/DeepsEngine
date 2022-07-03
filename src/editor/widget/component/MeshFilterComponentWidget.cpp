//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "MeshFilterComponentWidget.h"
#include "Component.h"
#include <iostream>
#include <QLabel>

MeshFilterComponentWidget::MeshFilterComponentWidget(QWidget *parent) {
    this->setVisible(false);

    // file select widget
    fileSelectWidget = new FileSelectWidget(this, "3D Model (*.obj *.fbx *.dae)");
    connect(fileSelectWidget, SIGNAL(fileSelected(std::string, std::string)), this, SLOT(onFileSelected(std::string, std::string)));

    // dropdown to select type of mesh filter
    QMenu* meshFilterTypeMenu = new QMenu;
    meshFilterTypeMenu->addAction("cube");
    meshFilterTypeMenu->addAction("static-model");
    meshFilterTypeMenu->addAction("animated-model");
    connect(meshFilterTypeMenu, SIGNAL(triggered(QAction*)), this, SLOT(onMeshFilterTypeMenuClicked(QAction*)));
    meshFilterBtn = new QPushButton("Mesh Filter Type");
    meshFilterBtn->setMenu(meshFilterTypeMenu);

    // create sample label
    meshFilterLabel = new QLabel("None");
    meshPathLabel = new QLabel("None");
    flipTexturesCheckbox = new QCheckBox("Flip Textures");
    QObject::connect(flipTexturesCheckbox, SIGNAL(clicked(bool)), this, SLOT(onFlipTexturesCheckboxSelected(bool)));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Mesh Filter"));
    mainLayout->addWidget(meshFilterBtn);
    mainLayout->addWidget(flipTexturesCheckbox);
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
        // TODO: generalize this by associating material component to model
        if (meshFilterComponent->mesh == "cube") {
            flipTexturesCheckbox->setVisible(false);
        } else {
            flipTexturesCheckbox->setVisible(true);
        }
        flipTexturesCheckbox->setCheckState(meshFilterComponent->flipTextures ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
        fileSelectWidget->setFilePath(meshFilterComponent->meshPath);
        meshFilterBtn->setText(QString::fromStdString(meshFilterComponent->mesh));
    }
}

void MeshFilterComponentWidget::onFileSelected(std::string relativeFilePath, std::string absoluteFilePath) {
    meshFilterComponent->setMeshPath(relativeFilePath);
}

void MeshFilterComponentWidget::onFlipTexturesCheckboxSelected(bool checked) {
    meshFilterComponent->flipTextures = checked;
    // force refresh the mesh
    meshFilterComponent->setMeshType(meshFilterComponent->mesh);
}

void MeshFilterComponentWidget::onMeshFilterTypeMenuClicked(QAction *action) {
    // get name of selected action from drop down menu
    std::string meshFilterTypeName = action->text().toStdString();
    meshFilterComponent->setMeshType(meshFilterTypeName);
    meshFilterBtn->setText(QString::fromStdString(meshFilterComponent->mesh));
}