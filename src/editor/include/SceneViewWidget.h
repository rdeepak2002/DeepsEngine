//
// Created by Deepak Ramalingam on 3/19/22.
//

#ifndef EDITOR_SCENEVIEWWIDGET_H
#define EDITOR_SCENEVIEWWIDGET_H


#include <QOpenGLWidget>
#include <QLineEdit>
#include <QHash>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include "Entity.h"
#include "EntitySelectListenerInterface.h"

class SceneViewWidget : public QWidget {
Q_OBJECT;

public:
    explicit SceneViewWidget(QWidget *parent = nullptr);
    ~SceneViewWidget();

public slots:
    void onListItemPressed(QTreeWidgetItem* item, int column);
    void addChildTreeItems(std::shared_ptr<DeepsEngine::Entity> entity, QTreeWidgetItem* treeItem);
    void onAddButtonPressed();
    void setEntitySelectListener(EntitySelectListenerInterface *entitySelectListenerInterface);

private:
    int timerId;
//    QListWidget *sceneViewList;
    QTreeWidget *treeWidget;
    QPushButton *addButton;
    std::vector<DeepsEngine::Entity> entities;
    EntitySelectListenerInterface *entitySelectListenerInterface;
    QHash<QTreeWidgetItem*, std::shared_ptr<DeepsEngine::Entity>> *entityItemMap;
    void refreshSceneViewItems();

protected:
    void timerEvent(QTimerEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};


#endif //EDITOR_SCENEVIEWWIDGET_H
