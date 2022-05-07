#include <QLabel>
#include "MainWindow.h"
#include "OpenGLWidget.h"
#include "Entity.h"
#include "ConsoleWidget.h"
#include "SceneViewWidget.h"

using std::filesystem::current_path;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // set gl version
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

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

    // opengl widget
    OpenGLWidget* openGLWidget = new OpenGLWidget(this);

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
    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

    // Set QWidget as the central layout of the main window
    setCentralWidget(window);

    // run web build process
//    QString resourceFileDirectory = QString::fromStdString(current_path().append("assets").append("res"));
//    QString resourceFileDirectory = QString("/Users/deepakramalingam/Documents/Projects/DeepsEngine/res");
//    std::string webBuildPath = current_path().append("assets").append("res").append("build").append("web");
//    std::string webBuildPath="/Users/deepakramalingam/Documents/Projects/DeepsEngine/src/build/web/";
    // TODO: fix directories (just have builds in same folder as project in some writeable directory for simplicity?)

    // menu bar items
    QMenu *fileMenu = new QMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    menuBar()->addAction(fileMenu->menuAction());

    connect(closeAction, &QAction::triggered, qApp, QApplication::quit);

    QMenu *buildMenu = new QMenu("Build");
    QAction* webBuildAction = buildMenu->addAction("Web");
    menuBar()->addAction(buildMenu->menuAction());

    connect(webBuildAction, SIGNAL(triggered()), this, SLOT(buildWeb()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem) {
    inspectorWidget->onEntitySelected(entity, listItem);
}

void MainWindow::buildWeb() {
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
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
