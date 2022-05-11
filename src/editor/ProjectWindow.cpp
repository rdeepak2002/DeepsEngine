#include <QLabel>
#include <QDir>
#include <QFileDialog>
#include "ProjectWindow.h"
#include "OpenGLWidget.h"
#include "Entity.h"
#include "ConsoleWidget.h"
#include "SceneViewWidget.h"
#include "ProjectWidget.h"
#include "ProjectsWidget.h"

using std::filesystem::current_path;

ProjectWindow::ProjectWindow(QWidget *parent) : QMainWindow(parent)
{
    // prompt user to open project path
//    QString projectPath = QFileDialog::getExistingDirectory(this, tr("Open project"), QDir::homePath());
//    Application::getInstance().setProjectPath(projectPath.toStdString());
//    Application::getInstance().createSampleEntities();

    // set initial window size
    double startWidth = QDesktopWidget().availableGeometry(this).size().width() * 0.95;
    double startHeight = QDesktopWidget().availableGeometry(this).size().height() * 0.8;
    resize(startWidth, startHeight);

    // move window to center of screen
    QSize screenGeometry = QDesktopWidget().availableGeometry(this).size();
    int startX = (screenGeometry.width()-this->width()) / 2;
    int startY = (screenGeometry.height()-this->height()) / 2;
    move(startX, startY);

    // set window title
    this->setWindowTitle("Deeps Engine");

    this->show();

    // Set QWidget as the central layout of the main window
//    ProjectWidget* projectWidget = new ProjectWidget(this);
//    projectWidget->show();
//    projectWidget->setWindowTitle("DeepsEngine Project");

//    ProjectsWidget* projectsWidget = new ProjectsWidget(this);
//    projectsWidget->show();
//    projectsWidget->setWindowTitle("DeepsEngine");

//    showProjectsWindow();

    // hide this main window (initially show it to make the menu bar appear)
//    this->show();
    this->close();
    showProjectsWindow();
}

ProjectWindow::~ProjectWindow()
{
}

void ProjectWindow::showProjectWindow() {
    ProjectWidget* projectWidget = new ProjectWidget(this);
    projectWidget->show();
    std::string projectPath = Application::getInstance().getProjectPath().u8string();
    projectWidget->setWindowTitle(QString::fromStdString(projectPath));
}

void ProjectWindow::showProjectsWindow() {
    ProjectsWidget* projectsWidget = new ProjectsWidget(this);
    projectsWidget->show();
    projectsWidget->setWindowTitle("Welcome to DeepsEngine");
}

void ProjectWindow::buildWeb() {
    // update the builds to the latest version
    updateBuilds();

    // create web build
    std::string resourcePath = Application::getInstance().getProjectPath().append("src");
    std::string buildDirectory = Application::getInstance().getProjectPath().append("build").append("web");
    std::string terminalCommand = "export DEEPS_ENGINE_RESOURCE_DIRECTORY=" + resourcePath + " && cd " + buildDirectory + " && " + "./build.sh";

    FILE *fp;
    char path[1035];

    fp = popen(terminalCommand.c_str(), "r");
    if (fp == NULL) {
        Logger::Error("Failed to create web build");
    } else {
        while (fgets(path, sizeof(path), fp) != NULL) {
            printf("%s", path);
            Logger::Debug("Web build: " + std::string(path));
        }

        pclose(fp);
    }
}

void ProjectWindow::updateBuilds() {
    std::string projectDirectory = Application::getInstance().getProjectPath();
    std::string terminalCommand = "cd " + projectDirectory + " && ./update-builds.sh";

    FILE *fp;
    char path[1035];

    fp = popen(terminalCommand.c_str(), "r");
    if (fp == NULL) {
        Logger::Error("Failed to update builds");
    } else {
        while (fgets(path, sizeof(path), fp) != NULL) {
            printf("%s", path);
            Logger::Debug("Build update: " + std::string(path));
        }

        pclose(fp);
    }
}
