#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OpenGLCubeWidget.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenGLCubeWidget* openGlCubeWidget = new OpenGLCubeWidget(this);
    this->layout()->addWidget(openGlCubeWidget);
}

MainWindow::~MainWindow()
{
}
