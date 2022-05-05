//
// Created by Deepak Ramalingam on 3/24/22.
//

#ifndef EDITOR_CONSOLEWIDGET_H
#define EDITOR_CONSOLEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "src/engine/header/LoggerCallbackInterface.h"

class ConsoleWidget: public QWidget, LoggerCallbackInterface {
Q_OBJECT;

public:
    explicit ConsoleWidget(QWidget *parent = nullptr);
    ~ConsoleWidget();
    void logCallback(std::string text);
private:
    QListWidget *listWidget;
};


#endif //EDITOR_CONSOLEWIDGET_H
