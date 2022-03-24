#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/editor/widget/OpenGLWidget.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include "src/editor/widget/SceneViewWidget.h"
#include "src/editor/widget/InspectorWidget.h"
#include "src/editor/widget/ConsoleWidget.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set gl version
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    // ui file
    ui->setupUi(this);

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
    sceneViewWidget = new SceneViewWidget;

    // inspector widget
    inspectorWidget = new InspectorWidget;

    // outer horizontal layout
    hLayout->addWidget(sceneViewWidget);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(inspectorWidget);

    // add horizontal layout to main layout
    mainLayout->addLayout(hLayout);

    // display the main layout
    ui->centralwidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onEntitySelected(DeepsEngine::Entity entity) {
    inspectorWidget->onEntitySelected(entity);
}