//
// Created by Deepak Ramalingam on 7/13/22.
//

#include "ProjectListWidgetItem.h"
#include <QVBoxLayout>
#include <QLabel>

ProjectListWidgetItem::ProjectListWidgetItem(QWidget *parent, QString projectPath) {
    setObjectName("ProjectListWidgetItem");
    item = new QListWidgetItem(projectPath);
    item->setSizeHint(QSize(0,65));

    // add widgets to main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignLeft);

    QLabel* imagePreviewLabel = new QLabel;
    QString imagePreviewImagePath = QString(projectPath)
            .append(QDir::separator())
            .append("sys")
            .append(QDir::separator())
            .append("preview.png");
    QPixmap imagePreview = QPixmap(imagePreviewImagePath);

    imagePreview = imagePreview.scaled(30, 30);
    imagePreviewLabel->setPixmap(imagePreview);
    imagePreviewLabel->setObjectName("imagePreviewLabel");
    imagePreviewLabel->setFixedSize(30, 30);
    mainLayout->addWidget(imagePreviewLabel);

    QVBoxLayout *projectDetailsLayout = new QVBoxLayout;
    std::string projectNameStr = projectPath.toStdString();
    std::basic_string<char>::size_type slashIndex = projectPath.toStdString().find_last_of(QDir::separator().toLatin1());
    if (slashIndex != std::string::npos) {
        projectNameStr = projectPath.toStdString().substr(slashIndex + 1);
    }
    QLabel* projectNameLabel = new QLabel(QString::fromStdString(projectNameStr));
    projectNameLabel->setObjectName("projectNameLabel");
    projectDetailsLayout->addWidget(projectNameLabel);

    QLabel* projectFilePathLabel = new QLabel(projectPath);
    projectFilePathLabel->setObjectName("projectFilePathLabel");
    projectDetailsLayout->addWidget(projectFilePathLabel);

    mainLayout->addLayout(projectDetailsLayout);

    setLayout(mainLayout);
}

ProjectListWidgetItem::~ProjectListWidgetItem() {

}

QListWidgetItem *ProjectListWidgetItem::getItem() {
    return item;
}
