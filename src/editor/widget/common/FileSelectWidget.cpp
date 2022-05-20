//
// Created by Deepak Ramalingam on 5/20/22.
//

#include "FileSelectWidget.h"

FileSelectWidget::FileSelectWidget(QWidget *parent) {
    // label and button
    filePathLabel = new ClickableLabel("no file");
    fileSelectButton = new QPushButton("Change");
    connect(fileSelectButton, SIGNAL(clicked()), this, SLOT(onChangeFileButtonPressed()));
    connect(filePathLabel , SIGNAL(clicked()), this, SLOT(onLabelClicked()));

    QHBoxLayout *fileChangeInputLayout = new QHBoxLayout;
    fileChangeInputLayout->addWidget(filePathLabel);
    fileChangeInputLayout->addWidget(fileSelectButton);
    this->setLayout(fileChangeInputLayout);
}

FileSelectWidget::~FileSelectWidget() {
    delete filePathLabel;
    delete fileSelectButton;
}

void FileSelectWidget::onChangeFileButtonPressed() {
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

            this->relativeFilePath = scriptRelativePathString;
            this->absoluteFilePath = fileName.toStdString();

            emit fileSelected(this->relativeFilePath, this->absoluteFilePath);

            OpenGLWidget::stopMouseTracking = false;
        }
    }
}

void FileSelectWidget::setFilePath(std::string filePath) {
    this->relativeFilePath = filePath;
    filePathLabel->setText(QString::fromStdString(filePath));
    this->absoluteFilePath = Application::getInstance().getProjectPath().append(filePath);
}

void FileSelectWidget::onLabelClicked() {
    emit clicked(this->relativeFilePath, this->absoluteFilePath);
}
