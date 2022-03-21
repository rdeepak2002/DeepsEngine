#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/editor/widget/OpenGLWidget.h"
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"
#include "src/editor/widget/SceneViewWidget.h"
#include "src/editor/widget/InspectorWidget.h"

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

    // addButton
    QPushButton* button = new QPushButton;
    button->setText("test addButton");

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
    vLayout->addWidget(consoleViewArea);

    // outer horizontal layout
    hLayout->addWidget(new SceneViewWidget);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(new InspectorWidget);

    // add horizontal layout to main layout
    mainLayout->addLayout(hLayout);

    // display the main layout
    ui->centralwidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onEntitySelected(DeepsEngine::Entity entity) {
    std::cout << "entity selected: " << entity.GetId() << std::endl;
}