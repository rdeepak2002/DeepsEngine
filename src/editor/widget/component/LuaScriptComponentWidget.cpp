//
// Created by Deepak Ramalingam on 5/13/22.
//

#include "LuaScriptComponentWidget.h"
#include "OpenGLWidget.h"

LuaScriptComponentWidget::LuaScriptComponentWidget(QWidget *parent) {
    this->setVisible(false);

//    // create sample label
//    scriptPathLabel = new QLabel("no script");
//
//    // button to change file
//    changeFileButton = new QPushButton("Change");
//
//    connect(changeFileButton, SIGNAL(clicked()), this, SLOT(onChangeFileButtonPressed()));

    fileSelectWidget = new FileSelectWidget;

    connect(fileSelectWidget, SIGNAL(fileSelected(std::string)), this, SLOT(onFileSelected(std::string)));

    // file change component
//    QHBoxLayout *fileChangeInputLayout = new QHBoxLayout;
//    fileChangeInputLayout->addWidget(scriptPathLabel);
//    fileChangeInputLayout->addWidget(changeFileButton);
//    fileChangeWidget->setLayout(fileChangeInputLayout);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Lua Script"));
    mainLayout->addWidget(fileSelectWidget);
    setLayout(mainLayout);
}

LuaScriptComponentWidget::~LuaScriptComponentWidget() {
//    delete scriptPathLabel;
}

void LuaScriptComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    luaScriptComponent = dynamic_cast<DeepsEngine::Component::LuaScript*>(component);

    if (luaScriptComponent) {
        fileSelectWidget->setFilePath(luaScriptComponent->scriptPath);
    }
}

void LuaScriptComponentWidget::onFileSelected(std::string relativeFilePath) {
    luaScriptComponent->changeScript(relativeFilePath);
}
