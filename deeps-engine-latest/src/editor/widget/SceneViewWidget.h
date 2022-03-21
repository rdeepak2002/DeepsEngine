//
// Created by Deepak Ramalingam on 3/19/22.
//

#ifndef EDITOR_SCENEVIEWWIDGET_H
#define EDITOR_SCENEVIEWWIDGET_H


#include <QOpenGLWidget>
#include <QLineEdit>
#include <QTextEdit>
#include "src/engine/scene/Entity.h"
#include "src/editor/mainwindow.h"

class SceneViewWidget : public QWidget {
Q_OBJECT;

public:
    explicit SceneViewWidget(QWidget *parent = nullptr);
    ~SceneViewWidget();

public slots:
    void onListItemPressed(QListWidgetItem* item);
    void onAddButtonPressed();

private:
    int timerId;
    QListWidget *sceneViewList;
    QPushButton *addButton;
    std::vector<DeepsEngine::Entity> entities;
    void refreshSceneViewItems();

protected:
    void timerEvent(QTimerEvent *event) override;
};


#endif //EDITOR_SCENEVIEWWIDGET_H
