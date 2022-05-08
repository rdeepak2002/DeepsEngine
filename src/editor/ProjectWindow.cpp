#include <QLabel>
#include <QDir>
#include <QFileDialog>
#include "ProjectWindow.h"
#include "OpenGLWidget.h"
#include "Entity.h"
#include "ConsoleWidget.h"
#include "SceneViewWidget.h"
#include "src/editor/widget/ProjectWidget.h"

using std::filesystem::current_path;

ProjectWindow::ProjectWindow(QWidget *parent) : QMainWindow(parent)
{
    // prompt user to open project path
    QString projectPath = QFileDialog::getExistingDirectory(this, tr("Open project"), QDir::homePath());
    Application::getInstance().setProjectPath(projectPath.toStdString());
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

    // set window title
    this->setWindowTitle("Deeps Engine");

    // menu bar items
    QMenu *fileMenu = new QMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    menuBar()->addAction(fileMenu->menuAction());

    connect(closeAction, &QAction::triggered, qApp, QApplication::quit);

    QMenu *buildMenu = new QMenu("Build");
    QAction* webBuildAction = buildMenu->addAction("Web");
    menuBar()->addAction(buildMenu->menuAction());

    connect(webBuildAction, SIGNAL(triggered()), this, SLOT(buildWeb()));

    // Set QWidget as the central layout of the main window
    ProjectWidget* projectWidget = new ProjectWidget;
    setCentralWidget(projectWidget);
}

ProjectWindow::~ProjectWindow()
{
}

void ProjectWindow::buildWeb() {
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    // TODO: fix directories (just have builds in same folder as project in some writeable directory for simplicity?)
    // TODO: refer to process directory
    env.insert("DEEPS_ENGINE_RESOURCE_DIRECTORY", "/Users/deepakramalingam/Documents/Projects/DeepsEngine/res");
    env.insert("DEEPS_ENGINE_WEB_SERVE_CONTENT_DETACHED", "true");
    QProcess *process = new QProcess(this);
    process->setProcessEnvironment(env);
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
