#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OpenGLCubeWidget.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set gl version
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    OpenGLCubeWidget* openGlCubeWidget = new OpenGLCubeWidget(this);
    this->layout()->addWidget(openGlCubeWidget);
}

MainWindow::~MainWindow()
{
}
