//
// Created by Deepak Ramalingam on 5/7/22.
//

#ifndef DEEPSENGINE_PROJECTWIDGET_H
#define DEEPSENGINE_PROJECTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHash>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "InspectorWidget.h"
#include "EntitySelectListenerInterface.h"
#include "ProjectWindow.h"

class ProjectWidget: public QWidget, EntitySelectListenerInterface {
Q_OBJECT;

public:
    explicit ProjectWidget(QWidget *parent = nullptr);
    ~ProjectWidget();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    ProjectWindow* projectWindow;
    QMenu *fileMenu;
    QMenu *buildMenu;
    InspectorWidget* inspectorWidget;
signals:
    void showProjectsWindow();
public slots:
    void onEntitySelected(QHash<QTreeWidgetItem*, std::shared_ptr<DeepsEngine::Entity>> *entityItemMap, QTreeWidgetItem* listItem) override;
    void saveProject();
};


#endif //DEEPSENGINE_PROJECTWIDGET_H
