//
// Created by Deepak Ramalingam on 5/7/22.
//

#include "ProjectsWidget.h"

ProjectsWidget::ProjectsWidget(QWidget *parent) {
    // reference to project window to modify menu bar
    projectWindow = dynamic_cast<ProjectWindow*>(parent);

    fileMenu = new QMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    projectWindow->menuBar()->addAction(fileMenu->menuAction());
    connect(closeAction, &QAction::triggered, qApp, QApplication::quit);

    // outer Layer
    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("new project button"));
    mainLayout->addWidget(new QLabel("TODO: list of projects"));
    setLayout(mainLayout);
}

ProjectsWidget::~ProjectsWidget() {

}

void ProjectsWidget::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    projectWindow->menuBar()->removeAction(fileMenu->menuAction());
}
