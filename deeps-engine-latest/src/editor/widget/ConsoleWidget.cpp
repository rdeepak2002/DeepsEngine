//
// Created by Deepak Ramalingam on 3/24/22.
//

#include "ConsoleWidget.h"
#include "src/engine/Logger.h"
#include <iostream>

ConsoleWidget::ConsoleWidget(QWidget *parent) {
    setMaximumHeight(200.0);

    // title for this panel
    QLabel* panelTitle = new QLabel("Console");;
    listWidget = new QListWidget;

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(panelTitle);
    mainLayout->addWidget(listWidget);
    setLayout(mainLayout);
    Logger::setConsoleWidget(this);
}

ConsoleWidget::~ConsoleWidget() {
    delete listWidget;
}

void ConsoleWidget::logCallback(std::string text) {
    if (listWidget) {
        listWidget->addItem(QString::fromStdString(text));
    }
}
