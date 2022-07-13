//
// Created by Deepak Ramalingam on 5/7/22.
//

#include "ProjectsWidget.h"

QString readStyleSheet(QString styleSheetName) {
    QFile file(qApp->applicationDirPath().append(QDir::separator())
        .append("assets").append(QDir::separator())
        .append("res").append(QDir::separator())
        .append("style").append(QDir::separator())
        .append(styleSheetName));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    return styleSheet;
}

ProjectsWidget::ProjectsWidget(QWidget *parent) {
    this->setStyleSheet(readStyleSheet("ProjectWindow.qss"));

    // reference to project window to modify menu bar
    projectWindow = dynamic_cast<ProjectWindow*>(parent);

    // be able to launch project window from here
    connect(this, SIGNAL(showProjectWindow()), projectWindow, SLOT(showProjectWindow()));

    // set initial window size
    double startWidth = 830.0;
    double startHeight = 625.0;
    resize(startWidth, startHeight);

    // move window to center of screen
    QSize screenGeometry = QDesktopWidget().availableGeometry(this).size();
    int startX = (screenGeometry.width()-this->width()) / 2;
    int startY = (screenGeometry.height()-this->height()) / 2;
    move(startX, startY);

    // show menu bar
    projectWindow->show();

    fileMenu = new QMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    projectWindow->menuBar()->addAction(fileMenu->menuAction());
    connect(closeAction, &QAction::triggered, qApp, QApplication::quit);

    projectWindow->close();

    // outer Layer
    auto *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    auto vLayoutLeft = new QVBoxLayout;
    auto vLayoutRight = new QVBoxLayout;
    vLayoutRight->setContentsMargins(10, 10, 10, 10);

    QWidget* leftWidget = new QWidget(this);
    leftWidget->setFixedWidth(215);
    leftWidget->setObjectName("leftPanel");

    auto hLayoutLogo = new QHBoxLayout;

    QPixmap logo(qApp->applicationDirPath().append(QDir::separator())
                         .append("assets").append(QDir::separator())
                         .append("res").append(QDir::separator())
                         .append("logo").append(QDir::separator())
                         .append("logo_30.png"));
    QLabel* logoLabel = new QLabel;
    logoLabel->setPixmap(logo);
    hLayoutLogo->addWidget(logoLabel);
    hLayoutLogo->setAlignment(Qt::AlignLeft);

    vLayoutLeft->addLayout(hLayoutLogo);

    auto vLayoutNameAndVersion = new QVBoxLayout;
    vLayoutNameAndVersion->setAlignment(Qt::AlignTop);
    vLayoutNameAndVersion->setSpacing(0);

    QLabel* programNameLabel = new QLabel("DeepsEngine");
    programNameLabel->setObjectName("programNameLabel");
    vLayoutNameAndVersion->addWidget(programNameLabel);

    QLabel* programVersionLabel = new QLabel(QString::fromStdString(static_cast<std::string>(XSTR(DEEPS_ENGINE_VERSION))));
    programVersionLabel->setObjectName("programVersionLabel");
    vLayoutNameAndVersion->addWidget(programVersionLabel);

    hLayoutLogo->addLayout(vLayoutNameAndVersion);

    vLayoutLeft->setAlignment(Qt::AlignTop);
    leftWidget->setLayout(vLayoutLeft);

    // button header with open and new buttons
    auto *buttonHeader = new QHBoxLayout;
    buttonHeader->setAlignment(Qt::AlignRight);

    QPushButton *newProjectButton = new QPushButton("New Project", this);
    newProjectButton->setFixedSize(110, 45);
    connect(newProjectButton, &QPushButton::released, this, &ProjectsWidget::createProject);
    buttonHeader->addWidget(newProjectButton);

    QPushButton *openProjectButton = new QPushButton("Open", this);
    openProjectButton->setFixedSize(80, 45);
    connect(openProjectButton, &QPushButton::released, this, &ProjectsWidget::promptOpenProject);
    buttonHeader->addWidget(openProjectButton);

    vLayoutRight->addLayout(buttonHeader);

    // list of projects
    QListWidget* qListWidget = new QListWidget();
    vLayoutRight->addWidget(qListWidget);

    mainLayout->addWidget(leftWidget);
    mainLayout->addLayout(vLayoutRight);
    setLayout(mainLayout);

    QSettings settings("DeepDev", "DeepsEngine");
    settings.beginGroup("ProjectsList");
    for (QString projectFilePath : settings.allKeys()) {
        QString filePrefix = QDir::separator();
        QFileInfo projectDirectoryInfo = QFileInfo(filePrefix + projectFilePath);
        if (projectDirectoryInfo.exists() && projectDirectoryInfo.isDir()) {
            qListWidget->addItem(projectFilePath);
        } else {
            Logger::Warn("Removing non existent file path: " + projectFilePath.toStdString());
            settings.remove(projectFilePath);
        }
    }
    settings.endGroup();

    connect(qListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onProjectsListClicked(QListWidgetItem*)));
}

ProjectsWidget::~ProjectsWidget() {

}

void ProjectsWidget::closeEvent(QCloseEvent *event) {
    projectWindow->menuBar()->removeAction(fileMenu->menuAction());
    QWidget::closeEvent(event);
}

void ProjectsWidget::promptOpenProject() {
    QString projectPath = QFileDialog::getExistingDirectory(this, tr("Open project"), QDir::homePath());
    if (!projectPath.isEmpty()) {
        openProject(projectPath);
    }
}

void ProjectsWidget::onProjectsListClicked(QListWidgetItem* item)
{
    QString projectPath = item->text();
    QString filePrefix = QDir::separator();

    if (!projectPath.isEmpty()) {
        openProject(filePrefix + projectPath);
    }
}

void ProjectsWidget::openProject(QString projectPath) {
    Logger::Debug("Opening project " + projectPath.toStdString());

    Application::getInstance().setProjectPath(projectPath.toStdString());

    QSettings settings("DeepDev", "DeepsEngine");
    settings.beginGroup("ProjectsList");
    settings.setValue(projectPath, "Project Name");
    settings.endGroup();

    emit showProjectWindow();
    this->close();
}

void ProjectsWidget::createProject() {
    QString projectPath = QFileDialog::getExistingDirectory(this, tr("New project folder"), QDir::homePath());
    QString blankProjectPath = qApp->applicationDirPath().append(QDir::separator()).append("assets").append(QDir::separator()).append("res").append(QDir::separator()).append("example-project");

    // TODO: make directory with name of the project similar to Jetbrains IDEs
    copyFolder(blankProjectPath, projectPath);

    if (!projectPath.isEmpty() && !blankProjectPath.isEmpty()) {
        openProject(projectPath);
    }
}

void ProjectsWidget::copyFolder(QString sourceFolder, QString destFolder)
{
    QDir sourceDir(sourceFolder);
    if(!sourceDir.exists()) {
        Logger::Error("Source directory does not exist: " + sourceFolder.toStdString());
        return;
    }
    QDir destDir(destFolder);
    if(!destDir.exists())
    {
        destDir.mkdir(destFolder);
    }
    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + QDir::separator() + files[i];
        QString destName = destFolder + QDir::separator() + files[i];
        QFile::copy(srcName, destName);
    }
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + QDir::separator() + files[i];
        QString destName = destFolder + QDir::separator() + files[i];
        copyFolder(srcName, destName);
    }
}