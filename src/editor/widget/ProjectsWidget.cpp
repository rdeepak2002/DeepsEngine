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

    // show menu bar
    projectWindow->show();

    fileMenu = new QMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    projectWindow->menuBar()->addAction(fileMenu->menuAction());
    connect(closeAction, &QAction::triggered, qApp, QApplication::quit);

    projectWindow->close();

    // outer Layer
    auto *mainLayout = new QVBoxLayout;

    QPushButton *newProjectButton = new QPushButton("New Project", this);
    connect(newProjectButton, &QPushButton::released, this, &ProjectsWidget::createProject);
    mainLayout->addWidget(newProjectButton);

    QPushButton *openProjectButton = new QPushButton("Open Project", this);
    connect(openProjectButton, &QPushButton::released, this, &ProjectsWidget::promptOpenProject);
    mainLayout->addWidget(openProjectButton);

    QListWidget* qListWidget = new QListWidget();
    qListWidget->setStyleSheet(qListWidget->styleSheet().append("background-color: transparent;"));
    mainLayout->addWidget(qListWidget);

    setLayout(mainLayout);

    QSettings settings("DeepDev", "DeepsEngine");
    settings.beginGroup("ProjectsList");
    for (QString projectFilePath : settings.allKeys()) {
        QString filePrefix = QDir::separator();
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
    projectWindow->menuBar()->removeAction(fileMenu->menuAction());
    QWidget::closeEvent(event);
}

void ProjectsWidget::promptOpenProject() {
    QString projectPath = QFileDialog::getExistingDirectory(this, tr("Open project"), QDir::homePath());
    if (!projectPath.isEmpty()) {
        openProject(projectPath);
    }
}

void ProjectsWidget::onProjectsListClicked(QListWidgetItem* item)
{
    QString projectPath = item->text();
    QString filePrefix = QDir::separator();

    if (!projectPath.isEmpty()) {
        openProject(filePrefix + projectPath);
    }
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

void ProjectsWidget::createProject() {
    QString projectPath = QFileDialog::getExistingDirectory(this, tr("New project folder"), QDir::homePath());
    QString blankProjectPath = qApp->applicationDirPath().append(QDir::separator()).append("assets").append(QDir::separator()).append("res").append(QDir::separator()).append("example-project");

    // TODO: make directory with name of the project similar to Jetbrains IDEs
    copyFolder(blankProjectPath, projectPath);

    if (!projectPath.isEmpty() && !blankProjectPath.isEmpty()) {
        openProject(projectPath);
    }
}

void ProjectsWidget::copyFolder(QString sourceFolder, QString destFolder)
{
    QDir sourceDir(sourceFolder);
    if(!sourceDir.exists()) {
        Logger::Error("Source directory does not exist: " + sourceFolder.toStdString());
        return;
    }
    QDir destDir(destFolder);
    if(!destDir.exists())
    {
        destDir.mkdir(destFolder);
    }
    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + QDir::separator() + files[i];
        QString destName = destFolder + QDir::separator() + files[i];
        QFile::copy(srcName, destName);
    }
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + QDir::separator() + files[i];
        QString destName = destFolder + QDir::separator() + files[i];
        copyFolder(srcName, destName);
    }
}