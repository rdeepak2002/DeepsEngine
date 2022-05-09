//
// Created by Deepak Ramalingam on 5/7/22.
//

#include "ProjectsWidget.h"

ProjectsWidget::ProjectsWidget(QWidget *parent) {
    // reference to project window to modify menu bar
    projectWindow = dynamic_cast<ProjectWindow*>(parent);

    // be able to launch project window from here
    connect(this, SIGNAL(showProjectWindow()), projectWindow, SLOT(showProjectWindow()));

    // set initial window size
    double startWidth = 800.0;
    double startHeight = 650.0;
    resize(startWidth, startHeight);

    // move window to center of screen
    QSize screenGeometry = QDesktopWidget().availableGeometry(this).size();
    int startX = (screenGeometry.width()-this->width()) / 2;
    int startY = (screenGeometry.height()-this->height()) / 2;
    move(startX, startY);

    fileMenu = new QMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    projectWindow->menuBar()->addAction(fileMenu->menuAction());
    connect(closeAction, &QAction::triggered, qApp, QApplication::quit);

    // outer Layer
    auto *mainLayout = new QVBoxLayout;
    QPushButton *button = new QPushButton("Open Project", this);
    mainLayout->addWidget(button);
    connect(button, &QPushButton::released, this, &ProjectsWidget::promptOpenProject);
    QListWidget* qListWidget = new QListWidget();
    mainLayout->addWidget(qListWidget);
    setLayout(mainLayout);

    QSettings settings("DeepDev", "DeepsEngine");
    settings.beginGroup("ProjectsList");
    for (QString projectFilePath : settings.allKeys()) {
        // TODO: fix this for windows
        QString filePrefix = "/";
        QFileInfo projectDirectoryInfo = QFileInfo(filePrefix + projectFilePath);
        if (projectDirectoryInfo.exists() && projectDirectoryInfo.isDir()) {
            qListWidget->addItem(projectFilePath);
        } else {
            Logger::Warn("Removing non existent file path: " + projectFilePath.toStdString());
            settings.remove(projectFilePath);
        }
    }
    settings.endGroup();

    connect(qListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onProjectsListClicked(QListWidgetItem*)));
}

ProjectsWidget::~ProjectsWidget() {

}

void ProjectsWidget::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    projectWindow->menuBar()->removeAction(fileMenu->menuAction());
}

void ProjectsWidget::promptOpenProject() {
    QString projectPath = QFileDialog::getExistingDirectory(this, tr("Open project"), QDir::homePath());
    openProject(projectPath);
}

void ProjectsWidget::onProjectsListClicked(QListWidgetItem* item)
{
    QString projectPath = item->text();
    QString filePrefix = "/";
    openProject(filePrefix + projectPath);
}

void ProjectsWidget::openProject(QString projectPath) {
    Logger::Debug("Opening project " + projectPath.toStdString());

    Application::getInstance().setProjectPath(projectPath.toStdString());

    QSettings settings("DeepDev", "DeepsEngine");
    settings.beginGroup("ProjectsList");
    settings.setValue(projectPath, "Project Name");
    settings.endGroup();

    emit showProjectWindow();
    this->close();
}
