//
// Created by Deepak Ramalingam on 5/12/22.
//

#include "LightComponentWidget.h"

LightComponentWidget::LightComponentWidget(QWidget *parent) {
    // create sample label
    lightLabel = new QLabel("None");

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Type"));
    mainLayout->addWidget(lightLabel);
    setLayout(mainLayout);
}

LightComponentWidget::~LightComponentWidget() {

}

void LightComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    lightComponent = dynamic_cast<DeepsEngine::Component::Light*>(component);

    if (lightComponent) {
        lightLabel->setText(QString::fromStdString(lightComponent->type));
    }
}