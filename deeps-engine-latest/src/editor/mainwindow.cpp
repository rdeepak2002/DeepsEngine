#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/editor/widget/OpenGLWidget.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set gl version
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    // ui file
    ui->setupUi(this);

    // opengl widget
    OpenGLWidget* openGLWidget = new OpenGLWidget(this);

    // button
    QPushButton* button = new QPushButton;
    button->setText("test button");

    // outer Layer
    auto *mainLayout = new QVBoxLayout;

    // horizontal layout
    QHBoxLayout *hLayout = new QHBoxLayout;

    // vertical layout
    QVBoxLayout *vLayout = new QVBoxLayout;

    // scene view
    QListWidget *sceneViewScrollArea = new QListWidget;
    sceneViewScrollArea->addItem("test 1");

    // TODO: the crashing is due to the ".scene" call
    // TODO: maybe dont make scene variable a pointer?
    std::cout << "number of entities for scene view: " << Renderer::getInstance().scene.GetEntities().size() << std::endl;
    for(auto entity : Renderer::getInstance().scene.GetEntities()) {
        sceneViewScrollArea->addItem("test 1");
    }

    // console view
    QWidget *consoleViewArea = new QWidget;

    // inspector
    QScrollArea *inspectorScrollArea = new QScrollArea;

    // center vertical layout
    vLayout->addWidget(openGLWidget);
    vLayout->addWidget(consoleViewArea);

    // outer horizontal layout
    hLayout->addWidget(sceneViewScrollArea);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(inspectorScrollArea);

    // add horizontal layout to main layout
    mainLayout->addLayout(hLayout);

    // display the main layout
    ui->centralwidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}
