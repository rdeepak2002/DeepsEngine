//
// Created by Deepak Ramalingam on 5/12/22.
//

#include "LightComponentWidget.h"
#include <QMenu>
#include <QAction>

LightComponentWidget::LightComponentWidget(QWidget *parent) {
    // dropdown to select type of light
    QMenu* lightTypeMenu = new QMenu;
    lightTypeMenu->addAction("Directional");
    lightTypeMenu->addAction("Point");
    lightTypeMenu->addAction("Spotlight");
    connect(lightTypeMenu, SIGNAL(triggered(QAction*)), this, SLOT(onLightTypeMenuClicked(QAction*)));

    // create sample label
    lightTypeBtn = new QPushButton("Light Type");
    lightTypeBtn->setMenu(lightTypeMenu);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Light"));
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Type"));
    mainLayout->addWidget(lightTypeBtn);
    setLayout(mainLayout);
}

LightComponentWidget::~LightComponentWidget() {

}

void LightComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    lightComponent = dynamic_cast<DeepsEngine::Component::Light*>(component);

    if (lightComponent) {
        updateLightDropDownText();
    }
}

void LightComponentWidget::onLightTypeMenuClicked(QAction *action) {
    // get name of selected action from drop down menu
    std::string lightTypeName = action->text().toStdString();

    if (lightTypeName == "Directional") {
        lightComponent->type = "directional";
    } else if (lightTypeName == "Point") {
        lightComponent->type = "point";
    } else if (lightTypeName == "Spotlight") {
        lightComponent->type = "spotlight";
    }

    if (lightComponent) {
        updateLightDropDownText();
    }
}

void LightComponentWidget::updateLightDropDownText() {
    std::string lightType = lightComponent->type;
    if (!lightType.empty()) {
        lightType[0] = toupper(lightType[0]);
    }
    lightTypeBtn->setText(QString::fromStdString(lightType));
}
