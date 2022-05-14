//
// Created by Deepak Ramalingam on 5/13/22.
//

#include "LuaScriptComponentWidget.h"

LuaScriptComponentWidget::LuaScriptComponentWidget(QWidget *parent) {
    this->setVisible(false);

    // create sample label
    scriptPathLabel = new QLabel("no script");

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Lua Script"));
    mainLayout->addWidget(new QLabel("Path"));
    mainLayout->addWidget(scriptPathLabel);
    setLayout(mainLayout);
}

LuaScriptComponentWidget::~LuaScriptComponentWidget() {
    delete scriptPathLabel;
}

void LuaScriptComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    luaScriptComponent = dynamic_cast<DeepsEngine::Component::LuaScript*>(component);

    if (luaScriptComponent) {
        scriptPathLabel->setText(QString::fromStdString(luaScriptComponent->scriptPath));
    }
}
