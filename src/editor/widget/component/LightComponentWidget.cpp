//
// Created by Deepak Ramalingam on 5/12/22.
//

#include "LightComponentWidget.h"
#include <QMenu>
#include <QAction>

LightComponentWidget::LightComponentWidget(QWidget *parent) {
    // ambient r input
    ambientRInput = new QLineEdit;
    ambientRInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    ambientRInput->setPlaceholderText("r");
    connect(ambientRInput, SIGNAL(textChanged(const QString &)), this, SLOT(onAmbientRInputChange()));

    // ambient g input
    ambientGInput = new QLineEdit;
    ambientGInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    ambientGInput->setPlaceholderText("g");
    connect(ambientGInput, SIGNAL(textChanged(const QString &)), this, SLOT(onAmbientGInputChange()));

    // ambient b input
    ambientBInput = new QLineEdit;
    ambientBInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    ambientBInput->setPlaceholderText("b");
    connect(ambientBInput, SIGNAL(textChanged(const QString &)), this, SLOT(onAmbientBInputChange()));

    // diffuse r input
    diffuseRInput = new QLineEdit;
    diffuseRInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    diffuseRInput->setPlaceholderText("r");
    connect(diffuseRInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDiffuseRInputChange()));

    // diffuse g input
    diffuseGInput = new QLineEdit;
    diffuseGInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    diffuseGInput->setPlaceholderText("g");
    connect(diffuseGInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDiffuseGInputChange()));

    // diffuse b input
    diffuseBInput = new QLineEdit;
    diffuseBInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    diffuseBInput->setPlaceholderText("b");
    connect(diffuseBInput, SIGNAL(textChanged(const QString &)), this, SLOT(onDiffuseBInputChange()));

    // specular r input
    specularRInput = new QLineEdit;
    specularRInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    specularRInput->setPlaceholderText("r");
    connect(specularRInput, SIGNAL(textChanged(const QString &)), this, SLOT(onSpecularRInputChange()));

    // specular g input
    specularGInput = new QLineEdit;
    specularGInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    specularGInput->setPlaceholderText("g");
    connect(specularGInput, SIGNAL(textChanged(const QString &)), this, SLOT(onSpecularGInputChange()));

    // specular b input
    specularBInput = new QLineEdit;
    specularBInput->setValidator(new QDoubleValidator(0, 1, 3, this));
    specularBInput->setPlaceholderText("b");
    connect(specularBInput, SIGNAL(textChanged(const QString &)), this, SLOT(onSpecularBInputChange()));

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

    // constant input
    constantInput = new QLineEdit;
    constantInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    constantInput->setPlaceholderText("constant");
    connect(constantInput, SIGNAL(textChanged(const QString &)), this, SLOT(onConstantInputChange()));

    // linear input
    linearInput = new QLineEdit;
    linearInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    linearInput->setPlaceholderText("linear");
    connect(linearInput, SIGNAL(textChanged(const QString &)), this, SLOT(onLinearInputChange()));

    // quadratic input
    quadraticInput = new QLineEdit;
    quadraticInput->setValidator(new QDoubleValidator(-999999, 999999, 3, this));
    quadraticInput->setPlaceholderText("quadratic");
    connect(linearInput, SIGNAL(textChanged(const QString &)), this, SLOT(onQuadraticInputChange()));

    // dropdown to select type of light
    QMenu* lightTypeMenu = new QMenu;
    lightTypeMenu->addAction("Directional");
    lightTypeMenu->addAction("Point");
    lightTypeMenu->addAction("Spotlight");
    connect(lightTypeMenu, SIGNAL(triggered(QAction*)), this, SLOT(onLightTypeMenuClicked(QAction*)));
    lightTypeBtn = new QPushButton("Light Type");
    lightTypeBtn->setMenu(lightTypeMenu);

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

    // input fields for specular
    QHBoxLayout* specularInputFieldsGroup = new QHBoxLayout;
    specularInputFieldsGroup->addWidget(new QLabel("r"));
    specularInputFieldsGroup->addWidget(specularRInput);
    specularInputFieldsGroup->addWidget(new QLabel("g"));
    specularInputFieldsGroup->addWidget(specularGInput);
    specularInputFieldsGroup->addWidget(new QLabel("b"));
    specularInputFieldsGroup->addWidget(specularBInput);

    // group fields together
    lightTypeGroup = new QWidget;
    QVBoxLayout* lightTypeGroupLayout = new QVBoxLayout;
    lightTypeGroupLayout->addWidget(new QLabel("Type"));
    lightTypeGroupLayout->addWidget(lightTypeBtn);
    lightTypeGroup->setLayout(lightTypeGroupLayout);

    cutOffGroup = new QWidget;
    QVBoxLayout* cutOffGroupLayout = new QVBoxLayout;
    cutOffGroupLayout->addWidget(new QLabel("Cut Off"));
    cutOffGroupLayout->addWidget(cutOffInput);
    cutOffGroup->setLayout(cutOffGroupLayout);

    outerCutOffGroup = new QWidget;
    QVBoxLayout* outerCutOffGroupLayout = new QVBoxLayout;
    outerCutOffGroupLayout->addWidget(new QLabel("Outer Cut Off"));
    outerCutOffGroupLayout->addWidget(outerCutOffInput);
    outerCutOffGroup->setLayout(outerCutOffGroupLayout);

    ambientGroup = new QWidget;
    QVBoxLayout* ambientGroupLayout = new QVBoxLayout;
    ambientGroupLayout->addWidget(new QLabel("Ambient"));
    ambientGroupLayout->addLayout(ambientInputFieldsGroup);
    ambientGroup->setLayout(ambientGroupLayout);

    diffuseGroup = new QWidget;
    QVBoxLayout* diffuseGroupLayout = new QVBoxLayout;
    diffuseGroupLayout->addWidget(new QLabel("Diffuse"));
    diffuseGroupLayout->addLayout(diffuseInputFieldsGroup);
    diffuseGroup->setLayout(diffuseGroupLayout);

    specularGroup = new QWidget;
    QVBoxLayout* specularGroupLayout = new QVBoxLayout;
    specularGroupLayout->addWidget(new QLabel("Specular"));
    specularGroupLayout->addLayout(specularInputFieldsGroup);
    specularGroup->setLayout(specularGroupLayout);

    constantGroup = new QWidget;
    QVBoxLayout* constantGroupLayout = new QVBoxLayout;
    constantGroupLayout->addWidget(new QLabel("Constant"));
    constantGroupLayout->addWidget(constantInput);
    constantGroup->setLayout(constantGroupLayout);

    linearGroup = new QWidget;
    QVBoxLayout* linearGroupLayout = new QVBoxLayout;
    linearGroupLayout->addWidget(new QLabel("Linear"));
    linearGroupLayout->addWidget(linearInput);
    linearGroup->setLayout(linearGroupLayout);

    quadraticGroup = new QWidget;
    QVBoxLayout* quadraticGroupLayout = new QVBoxLayout;
    quadraticGroupLayout->addWidget(new QLabel("Quadratic"));
    quadraticGroupLayout->addWidget(quadraticInput);
    quadraticGroup->setLayout(quadraticGroupLayout);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Light"));
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(lightTypeGroup);
    mainLayout->addWidget(cutOffGroup);
    mainLayout->addWidget(outerCutOffGroup);
    mainLayout->addWidget(ambientGroup);
    mainLayout->addWidget(diffuseGroup);
    mainLayout->addWidget(specularGroup);
    mainLayout->addWidget(constantGroup);
    mainLayout->addWidget(linearGroup);
    mainLayout->addWidget(quadraticGroup);
    setLayout(mainLayout);

    hideAllLightConfigOptions();
}

LightComponentWidget::~LightComponentWidget() {

}

void LightComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    lightComponent = dynamic_cast<DeepsEngine::Component::Light*>(component);

    hideAllLightConfigOptions();

    if (lightComponent) {
        updateLightDropDownText();

        cutOffInput->setText(QString::fromStdString(std::to_string(lightComponent->cutOff)));
        outerCutOffInput->setText(QString::fromStdString(std::to_string(lightComponent->outerCutOff)));

        ambientRInput->setText(QString::fromStdString(std::to_string(lightComponent->ambient.x)));
        ambientGInput->setText(QString::fromStdString(std::to_string(lightComponent->ambient.y)));
        ambientBInput->setText(QString::fromStdString(std::to_string(lightComponent->ambient.z)));

        diffuseRInput->setText(QString::fromStdString(std::to_string(lightComponent->diffuse.x)));
        diffuseGInput->setText(QString::fromStdString(std::to_string(lightComponent->diffuse.y)));
        diffuseBInput->setText(QString::fromStdString(std::to_string(lightComponent->diffuse.z)));

        specularRInput->setText(QString::fromStdString(std::to_string(lightComponent->specular.x)));
        specularGInput->setText(QString::fromStdString(std::to_string(lightComponent->specular.y)));
        specularBInput->setText(QString::fromStdString(std::to_string(lightComponent->specular.z)));

        constantInput->setText(QString::fromStdString(std::to_string(lightComponent->constant)));
        linearInput->setText(QString::fromStdString(std::to_string(lightComponent->linear)));
        quadraticInput->setText(QString::fromStdString(std::to_string(lightComponent->quadratic)));

        showNecessaryLightConfigOptions();
    }
}

void LightComponentWidget::onLightTypeMenuClicked(QAction *action) {
    hideAllLightConfigOptions();

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
    showNecessaryLightConfigOptions();

    std::string lightType = lightComponent->type;
    if (!lightType.empty()) {
        lightType[0] = toupper(lightType[0]);
    }

    lightTypeBtn->setText(QString::fromStdString(lightType));
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

void LightComponentWidget::onSpecularRInputChange() {
    lightComponent->specular.x = specularRInput->text().toFloat();
}

void LightComponentWidget::onSpecularGInputChange() {
    lightComponent->specular.y = specularGInput->text().toFloat();
}

void LightComponentWidget::onSpecularBInputChange() {
    lightComponent->specular.z = specularBInput->text().toFloat();
}

void LightComponentWidget::onConstantInputChange() {
    lightComponent->constant = constantInput->text().toFloat();
}

void LightComponentWidget::onLinearInputChange() {
    lightComponent->linear = linearInput->text().toFloat();
}

void LightComponentWidget::onQuadraticInputChange() {
    lightComponent->quadratic = quadraticInput->text().toFloat();
}

void LightComponentWidget::hideAllLightConfigOptions() {
    ambientGroup->setVisible(false);
    diffuseGroup->setVisible(false);
    specularGroup->setVisible(false);

    constantGroup->setVisible(false);
    linearGroup->setVisible(false);
    quadraticGroup->setVisible(false);

    cutOffGroup->setVisible(false);
    outerCutOffGroup->setVisible(false);
}

void LightComponentWidget::showNecessaryLightConfigOptions() {
    if (!lightComponent) {
        return;
    }

    if (lightComponent->type == "directional") {
        ambientGroup->setVisible(true);
        diffuseGroup->setVisible(true);
        specularGroup->setVisible(true);
    } else if (lightComponent->type == "point") {
        ambientGroup->setVisible(true);
        diffuseGroup->setVisible(true);
        specularGroup->setVisible(true);

        constantGroup->setVisible(true);
        linearGroup->setVisible(true);
        quadraticGroup->setVisible(true);
    } else if (lightComponent->type == "spotlight") {
        ambientGroup->setVisible(true);
        diffuseGroup->setVisible(true);
        specularGroup->setVisible(true);

        constantGroup->setVisible(true);
        linearGroup->setVisible(true);
        quadraticGroup->setVisible(true);

        cutOffGroup->setVisible(true);
        outerCutOffGroup->setVisible(true);
    }
}
