//
// Created by Deepak Ramalingam on 6/26/22.
//

#include "NativeScriptComponentWidget.h"

NativeScriptComponentWidget::NativeScriptComponentWidget(QWidget *parent) {
    this->setVisible(false);

    fileSelectWidget = new FileSelectWidget(this, "cpp (*.cpp)");
    connect(fileSelectWidget, SIGNAL(fileSelected(std::string, std::string)), this, SLOT(onFileSelected(std::string, std::string)));
    connect(fileSelectWidget, SIGNAL(clicked(std::string, std::string)), this, SLOT(openFile(std::string, std::string)));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Native Script"));
    mainLayout->addWidget(fileSelectWidget);
    setLayout(mainLayout);
}

NativeScriptComponentWidget::~NativeScriptComponentWidget() {

}

void NativeScriptComponentWidget::setComponent(DeepsEngine::Component::Component *component) {
    nativeScriptComponent = dynamic_cast<DeepsEngine::Component::NativeScriptComponent*>(component);

    if (nativeScriptComponent) {
        fileSelectWidget->setFilePath(nativeScriptComponent->filePath);
    }
}

void NativeScriptComponentWidget::onFileSelected(std::string relativeFilePath, std::string absoluteFilePath) {
    nativeScriptComponent->changeScript(relativeFilePath);
}

void NativeScriptComponentWidget::openFile(std::string relativeFilePath, std::string absoluteFilePath) {
    // TODO: open with Clion

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

