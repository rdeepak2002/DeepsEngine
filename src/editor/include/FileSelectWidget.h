//
// Created by Deepak Ramalingam on 5/20/22.
//

#ifndef DEEPSENGINE_FILESELECTWIDGET_H
#define DEEPSENGINE_FILESELECTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
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
    explicit FileSelectWidget(QWidget *parent = nullptr);
    ~FileSelectWidget();
    void setFilePath(std::string filePath);
    std::string relativeFilePath;
public slots:
    void onChangeFileButtonPressed();
private:
    QLabel* filePathLabel;
    QPushButton* fileSelectButton;
signals:
    void fileSelected(std::string);
};


#endif //DEEPSENGINE_FILESELECTWIDGET_H
