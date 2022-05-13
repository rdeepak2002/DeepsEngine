//
// Created by Deepak Ramalingam on 5/12/22.
//

#include "LightComponentWidget.h"
#include <QMenu>
#include <QAction>

LightComponentWidget::LightComponentWidget(QWidget *parent) {
    // direction x input
    directionXInput = new QLineEdit;
    directionXInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    directionXInput->setPlaceholderText("x");
    connect(directionXInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDirectionXInputChange()));

    // direction y input
    directionYInput = new QLineEdit;
    directionYInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    directionYInput->setPlaceholderText("y");
    connect(directionYInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDirectionYInputChange()));

    // direction z input
    directionZInput = new QLineEdit;
    directionZInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    directionZInput->setPlaceholderText("z");
    connect(directionZInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDirectionZInputChange()));

    // ambient r input
    ambientRInput = new QLineEdit;
    ambientRInput->setValidator(new QDoubleValidator(-1, 1, 3, this));
    ambientRInput->setPlaceholderText("r");
    connect(ambientRInput, SIGNAL(textChanged(const QString &)), this, SLOT(onAmbientRInputChange()));

    // ambient g input
    ambientGInput = new QLineEdit;
    ambientGInput->setValidator(new QDoubleValidator(-1, 1, 3, this));
    ambientGInput->setPlaceholderText("g");
    connect(ambientGInput, SIGNAL(textChanged(const QString &)), this, SLOT(onAmbientGInputChange()));

    // ambient b input
    ambientBInput = new QLineEdit;
    ambientBInput->setValidator(new QDoubleValidator(-1, 1, 3, this));
    ambientBInput->setPlaceholderText("b");
    connect(ambientBInput, SIGNAL(textChanged(const QString &)), this, SLOT(onAmbientBInputChange()));

    // diffuse r input
    diffuseRInput = new QLineEdit;
    diffuseRInput->setValidator(new QDoubleValidator(-1, 1, 3, this));
    diffuseRInput->setPlaceholderText("r");
    connect(diffuseRInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDiffuseRInputChange()));

    // diffuse g input
    diffuseGInput = new QLineEdit;
    diffuseGInput->setValidator(new QDoubleValidator(-1, 1, 3, this));
    diffuseGInput->setPlaceholderText("g");
    connect(diffuseGInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDiffuseGInputChange()));

    // diffuse b input
    diffuseBInput = new QLineEdit;
    diffuseBInput->setValidator(new QDoubleValidator(-1, 1, 3, this));
    diffuseBInput->setPlaceholderText("b");
    connect(diffuseBInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDiffuseBInputChange()));

    // cut off input
    cutOffInput = new QLineEdit;
    cutOffInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    cutOffInput->setPlaceholderText("cut off");
    connect(cutOffInput, SIGNAL(textChanged(const QString &)), this, SLOT(onCutOffInputChange()));

    // outer cut off input
    outerCutOffInput = new QLineEdit;
    outerCutOffInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    outerCutOffInput->setPlaceholderText("outer cut off");
    connect(outerCutOffInput, SIGNAL(textChanged(const QString &)), this, SLOT(onOuterCutOffInputChange()));

    // dropdown to select type of light
    QMenu* lightTypeMenu = new QMenu;
    lightTypeMenu->addAction("Directional");
    lightTypeMenu->addAction("Point");
    lightTypeMenu->addAction("Spotlight");
    connect(lightTypeMenu, SIGNAL(triggered(QAction*)), this, SLOT(onLightTypeMenuClicked(QAction*)));
    lightTypeBtn = new QPushButton("Light Type");
    lightTypeBtn->setMenu(lightTypeMenu);

    // input fields for direction
    QHBoxLayout* directionInputFieldsGroup = new QHBoxLayout;
    directionInputFieldsGroup->addWidget(new QLabel("x"));
    directionInputFieldsGroup->addWidget(directionXInput);
    directionInputFieldsGroup->addWidget(new QLabel("y"));
    directionInputFieldsGroup->addWidget(directionYInput);
    directionInputFieldsGroup->addWidget(new QLabel("z"));
    directionInputFieldsGroup->addWidget(directionZInput);

    // input fields for ambient
    QHBoxLayout* ambientInputFieldsGroup = new QHBoxLayout;
    ambientInputFieldsGroup->addWidget(new QLabel("r"));
    ambientInputFieldsGroup->addWidget(ambientRInput);
    ambientInputFieldsGroup->addWidget(new QLabel("g"));
    ambientInputFieldsGroup->addWidget(ambientGInput);
    ambientInputFieldsGroup->addWidget(new QLabel("b"));
    ambientInputFieldsGroup->addWidget(ambientBInput);

    // input fields for diffuse
    QHBoxLayout* diffuseInputFieldsGroup = new QHBoxLayout;
    diffuseInputFieldsGroup->addWidget(new QLabel("r"));
    diffuseInputFieldsGroup->addWidget(diffuseRInput);
    diffuseInputFieldsGroup->addWidget(new QLabel("g"));
    diffuseInputFieldsGroup->addWidget(diffuseGInput);
    diffuseInputFieldsGroup->addWidget(new QLabel("b"));
    diffuseInputFieldsGroup->addWidget(diffuseBInput);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Light"));
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Type"));
    mainLayout->addWidget(lightTypeBtn);
    mainLayout->addWidget(new QLabel("Direction"));
    mainLayout->addLayout(directionInputFieldsGroup);
    mainLayout->addWidget(new QLabel("Cut Off"));
    mainLayout->addWidget(cutOffInput);
    mainLayout->addWidget(new QLabel("Outer Cut Off"));
    mainLayout->addWidget(outerCutOffInput);
    mainLayout->addWidget(new QLabel("Ambient"));
    mainLayout->addLayout(ambientInputFieldsGroup);
    mainLayout->addWidget(new QLabel("Diffuse"));
    mainLayout->addLayout(diffuseInputFieldsGroup);
    setLayout(mainLayout);
}

LightComponentWidget::~LightComponentWidget() {

}

void LightComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    lightComponent = dynamic_cast<DeepsEngine::Component::Light*>(component);

    if (lightComponent) {
        updateLightDropDownText();

        directionXInput->setText(QString::fromStdString(std::to_string(lightComponent->direction.x)));
        directionYInput->setText(QString::fromStdString(std::to_string(lightComponent->direction.y)));
        directionZInput->setText(QString::fromStdString(std::to_string(lightComponent->direction.z)));

        cutOffInput->setText(QString::fromStdString(std::to_string(lightComponent->cutOff)));
        outerCutOffInput->setText(QString::fromStdString(std::to_string(lightComponent->outerCutOff)));

        ambientRInput->setText(QString::fromStdString(std::to_string(lightComponent->ambient.x)));
        ambientGInput->setText(QString::fromStdString(std::to_string(lightComponent->ambient.y)));
        ambientBInput->setText(QString::fromStdString(std::to_string(lightComponent->ambient.z)));

        diffuseRInput->setText(QString::fromStdString(std::to_string(lightComponent->diffuse.x)));
        diffuseGInput->setText(QString::fromStdString(std::to_string(lightComponent->diffuse.y)));
        diffuseBInput->setText(QString::fromStdString(std::to_string(lightComponent->diffuse.z)));
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

void LightComponentWidget::onDirectionXInputChange() {
    lightComponent->direction.x = directionXInput->text().toFloat();
}

void LightComponentWidget::onDirectionYInputChange() {
    lightComponent->direction.y = directionYInput->text().toFloat();
}

void LightComponentWidget::onDirectionZInputChange() {
    lightComponent->direction.z = directionZInput->text().toFloat();
}

void LightComponentWidget::onCutOffInputChange() {
    lightComponent->cutOff = cutOffInput->text().toFloat();
}

void LightComponentWidget::onOuterCutOffInputChange() {
    lightComponent->outerCutOff = outerCutOffInput->text().toFloat();
}

void LightComponentWidget::onAmbientRInputChange() {
    lightComponent->ambient.x = ambientRInput->text().toFloat();
}

void LightComponentWidget::onAmbientGInputChange() {
    lightComponent->ambient.y = ambientGInput->text().toFloat();
}

void LightComponentWidget::onAmbientBInputChange() {
    lightComponent->ambient.z = ambientBInput->text().toFloat();
}

void LightComponentWidget::onDiffuseRInputChange() {
    lightComponent->diffuse.x = diffuseRInput->text().toFloat();
}

void LightComponentWidget::onDiffuseGInputChange() {
    lightComponent->diffuse.y = diffuseGInput->text().toFloat();
}

void LightComponentWidget::onDiffuseBInputChange() {
    lightComponent->diffuse.z = diffuseBInput->text().toFloat();
}

