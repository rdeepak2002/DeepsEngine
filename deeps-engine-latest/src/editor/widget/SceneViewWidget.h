//
// Created by Deepak Ramalingam on 3/19/22.
//

#ifndef EDITOR_SCENEVIEWWIDGET_H
#define EDITOR_SCENEVIEWWIDGET_H


#include <QOpenGLWidget>
#include <QLineEdit>
#include <QTextEdit>

class SceneViewWidget : public QOpenGLWidget {
Q_OBJECT;

public:
    explicit SceneViewWidget(QWidget *parent = nullptr);
    ~SceneViewWidget();

private:
    QTextEdit *addressText;
};


#endif //EDITOR_SCENEVIEWWIDGET_H
