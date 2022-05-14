//
// Created by Deepak Ramalingam on 5/13/22.
//

#include "MaterialComponentWidget.h"

MaterialComponentWidget::MaterialComponentWidget(QWidget *parent) {
    this->setVisible(false);

    // create sample label
    diffuseTexturePathLabel = new QLabel("no diffuse texture");
    specularTexturePathLabel = new QLabel("no specular texture");
    shininessLineEdit = new QLineEdit;
    shininessLineEdit->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    shininessLineEdit->setPlaceholderText("shininess");
    connect(shininessLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onShininessInputChange()));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Material"));
    mainLayout->addWidget(new QLabel("Diffuse Texture"));
    mainLayout->addWidget(diffuseTexturePathLabel);
    mainLayout->addWidget(new QLabel("Specular Texture"));
    mainLayout->addWidget(specularTexturePathLabel);
    mainLayout->addWidget(new QLabel("Shininess"));
    mainLayout->addWidget(shininessLineEdit);
    setLayout(mainLayout);
}

MaterialComponentWidget::~MaterialComponentWidget() {
    delete diffuseTexturePathLabel;
    delete specularTexturePathLabel;
    delete shininessLineEdit;
}

void MaterialComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    materialComponent = dynamic_cast<DeepsEngine::Component::Material*>(component);

    if (materialComponent) {
        diffuseTexturePathLabel->setText(QString::fromStdString(materialComponent->diffuseTexturePath));
        specularTexturePathLabel->setText(QString::fromStdString(materialComponent->specularTexturePath));
        shininessLineEdit->setText(QString::fromStdString(std::to_string(materialComponent->shininess)));
    }
}

void MaterialComponentWidget::onShininessInputChange() {
    materialComponent->shininess = shininessLineEdit->text().toFloat();
}
