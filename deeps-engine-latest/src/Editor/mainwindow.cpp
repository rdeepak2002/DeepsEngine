#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OpenGLCubeWidget.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set gl version
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    // ui file
    ui->setupUi(this);

    // button
    QPushButton* button = new QPushButton;
    button->setText("asdf");

    // opengl widget
    OpenGLCubeWidget* openGlCubeWidget = new OpenGLCubeWidget(this);

    // Horizontal layout with 3 buttons
    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addWidget(openGlCubeWidget);

    // Outer Layer
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Add the previous two inner layouts
    mainLayout->addLayout(hLayout);

    ui->centralwidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}
