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
    projectWidget->setWindowTitle("DeepsEngine Project");
}

void ProjectWindow::showProjectsWindow() {
    ProjectsWidget* projectsWidget = new ProjectsWidget(this);
    projectsWidget->show();
    projectsWidget->setWindowTitle("DeepsEngine");
}

void ProjectWindow::buildWeb() {
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    // TODO: fix directories (just have builds in same folder as project in some writeable directory for simplicity?)
    // TODO: refer to process directory
    env.insert("DEEPS_ENGINE_RESOURCE_DIRECTORY", "/Users/deepakramalingam/Documents/Projects/DeepsEngine/res");
    env.insert("DEEPS_ENGINE_WEB_SERVE_CONTENT_DETACHED", "true");
    QProcess *process = new QProcess(this);
    process->setProcessEnvironment(env);
    // TODO: fix this
    process->setWorkingDirectory("/Users/deepakramalingam/Documents/Projects/DeepsEngine/src/build/web/");
    process->start("./build.sh");
    if(!process->waitForStarted())
        Logger::Error("Error creating web build");

    bool retval = false;

    QByteArray buffer;

    while ((retval = process->waitForFinished())) {
        buffer.append(process->readAll());
    }

    Logger::Debug(QString(buffer).toStdString());
}
