//
// Created by Deepak Ramalingam on 5/13/22.
//

#include "LuaScriptComponentWidget.h"
#include "OpenGLWidget.h"

LuaScriptComponentWidget::LuaScriptComponentWidget(QWidget *parent) {
    this->setVisible(false);


    fileSelectWidget = new FileSelectWidget;
    connect(fileSelectWidget, SIGNAL(fileSelected(std::string, std::string)), this, SLOT(onFileSelected(std::string, std::string)));
    connect(fileSelectWidget, SIGNAL(clicked(std::string, std::string)), this, SLOT(openFile(std::string, std::string)));

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

void LuaScriptComponentWidget::onFileSelected(std::string relativeFilePath, std::string absoluteFilePath) {
    luaScriptComponent->changeScript(relativeFilePath);
}

void LuaScriptComponentWidget::openFile(std::string relativeFilePath, std::string absoluteFilePath) {
    // open lua script file
    std::string terminalCommand = "/Applications/Visual\\ Studio\\ Code.app/Contents/Resources/app/bin/code -r " + absoluteFilePath;
    Logger::Debug("running terminal command: " + terminalCommand);

    FILE *fp;
    char path[1035];

    fp = popen(terminalCommand.c_str(), "r");
    if (fp == NULL) {
        Logger::Error("Failed to open lua script file using VS Code");
    } else {
        while (fgets(path, sizeof(path), fp) != NULL) {
            printf("%s", path);
//            Logger::Debug("File opened: " + std::string(path));
        }

        pclose(fp);
    }
}
