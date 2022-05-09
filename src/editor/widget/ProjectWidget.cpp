//
// Created by Deepak Ramalingam on 5/7/22.
//

#include "ProjectWidget.h"

#include <QLabel>
#include <QDir>
#include <QFileDialog>
#include "ProjectWindow.h"
#include "OpenGLWidget.h"
#include "Entity.h"
#include "ConsoleWidget.h"
#include "SceneViewWidget.h"

ProjectWidget::ProjectWidget(QWidget *parent) {
    Application::getInstance().createSampleEntities();

    // set initial window size
    double startWidth = QDesktopWidget().availableGeometry(this).size().width() * 0.95;
    double startHeight = QDesktopWidget().availableGeometry(this).size().height() * 0.8;
    resize(startWidth, startHeight);

    // move window to center of screen
    QSize screenGeometry = QDesktopWidget().availableGeometry(this).size();
    int startX = (screenGeometry.width()-this->width()) / 2;
    int startY = (screenGeometry.height()-this->height()) / 2;
    move(startX, startY);

    // reference to project window to modify menu bar
    projectWindow = dynamic_cast<ProjectWindow*>(parent);

    fileMenu = new QMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    projectWindow->menuBar()->addAction(fileMenu->menuAction());
    connect(closeAction, &QAction::triggered, qApp, QApplication::quit);

    buildMenu = new QMenu("Build");
    QAction* webBuildAction = buildMenu->addAction("Web");
    projectWindow->menuBar()->addAction(buildMenu->menuAction());
    connect(webBuildAction, SIGNAL(triggered()), parent, SLOT(buildWeb()));

    // opengl widget
    OpenGLWidget* openGLWidget = new OpenGLWidget;

    // outer Layer
    auto *mainLayout = new QVBoxLayout;

    // horizontal layout
    QHBoxLayout *hLayout = new QHBoxLayout;

    // vertical layout
    QVBoxLayout *vLayout = new QVBoxLayout;

    // console view
    QWidget *consoleViewArea = new QWidget;

    // center vertical layout
    vLayout->addWidget(openGLWidget);
    vLayout->addWidget(new ConsoleWidget);

    // scene view widget
    SceneViewWidget* sceneViewWidget = new SceneViewWidget;
    sceneViewWidget->setEntitySelectListener(this);

    // inspector widget
    inspectorWidget = new InspectorWidget;

    // outer horizontal layout
    hLayout->addWidget(sceneViewWidget);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(inspectorWidget);

    // add horizontal layout to main layout
    mainLayout->addLayout(hLayout);

    // Set layout in QWidget
    this->setLayout(mainLayout);
}

ProjectWidget::~ProjectWidget() {

}

void ProjectWidget::onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem) {
    inspectorWidget->onEntitySelected(entity, listItem);
}

void ProjectWidget::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    projectWindow->menuBar()->removeAction(buildMenu->menuAction());
    projectWindow->menuBar()->removeAction(fileMenu->menuAction());
}
