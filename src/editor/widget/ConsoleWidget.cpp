//
// Created by Deepak Ramalingam on 3/24/22.
//

#include "ConsoleWidget.h"
#include "src/engine/header/Logger.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

ConsoleWidget::ConsoleWidget(QWidget *parent) {
    setMaximumHeight(210.0);

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
        listWidget->addItem(QString::fromStdString(currentDateTime() + ": " + text));

        // cap logs
        int maxLogs = 100;

        if (listWidget->count() > maxLogs) {
            listWidget->takeItem(0);
        }
    }
}
