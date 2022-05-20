//
// Created by Deepak Ramalingam on 5/13/22.
//

#include "LuaScriptComponentWidget.h"
#include "OpenGLWidget.h"

LuaScriptComponentWidget::LuaScriptComponentWidget(QWidget *parent) {
    this->setVisible(false);

    // create sample label
    scriptPathLabel = new QLabel("no script");

    // button to change file
    changeFileButton = new QPushButton("Change");

    connect(changeFileButton, SIGNAL(clicked()), this, SLOT(onChangeFileButtonPressed()));

    // file change component
    QWidget* fileChangeWidget = new QWidget;
    QHBoxLayout *fileChangeInputLayout = new QHBoxLayout;
    fileChangeInputLayout->addWidget(scriptPathLabel);
    fileChangeInputLayout->addWidget(changeFileButton);
    fileChangeWidget->setLayout(fileChangeInputLayout);

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Lua Script"));
    mainLayout->addWidget(fileChangeWidget);
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

void LuaScriptComponentWidget::onChangeFileButtonPressed() {
    OpenGLWidget::stopMouseTracking = true;
    QWidget::setFocus();

    std::string caption = "Select file";
    std::string fileFilter = "lua (*.lua)";

    QFileDialog::Options options;
//    options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;

    std::string projectDirectoryString = Application::getInstance().getProjectPath();
    QString projectDirectory = QString::fromStdString(projectDirectoryString);

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(caption.c_str()),
                                                    projectDirectory,
                                                    tr(fileFilter.c_str()),
                                                    &selectedFilter,
                                                    options);

    if (!fileName.isEmpty()) {
        QDir dir(projectDirectory);
        QString scriptRelativeFilePath = dir.relativeFilePath(fileName);

        if (!scriptRelativeFilePath.isEmpty()) {
            std::string scriptRelativePathString = scriptRelativeFilePath.toStdString();

            Logger::Debug(scriptRelativePathString);

            luaScriptComponent->changeScript(scriptRelativePathString);
            scriptPathLabel->setText(QString::fromStdString(scriptRelativePathString));

            OpenGLWidget::stopMouseTracking = false;
        }
    }
}
