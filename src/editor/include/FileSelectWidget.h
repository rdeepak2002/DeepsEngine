//
// Created by Deepak Ramalingam on 5/20/22.
//

#ifndef DEEPSENGINE_FILESELECTWIDGET_H
#define DEEPSENGINE_FILESELECTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "ClickableLabel.h"
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"
#include "Application.h"
#include "OpenGLWidget.h"

class FileSelectWidget: public QWidget {
Q_OBJECT;
public:
    explicit FileSelectWidget(QWidget *parent, std::string fileFilter);
    ~FileSelectWidget();
    void setFilePath(std::string filePath);
    std::string relativeFilePath;
    std::string absoluteFilePath;
    std::string fileFilter;
public slots:
    void onChangeFileButtonPressed();
    void onLabelClicked();
private:
    QLabel* filePathLabel;
    QPushButton* fileSelectButton;
signals:
    void fileSelected(std::string relativePath, std::string absolutePath);
    void clicked(std::string relativePath, std::string absolutePath);
};


#endif //DEEPSENGINE_FILESELECTWIDGET_H
