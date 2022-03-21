//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_INSPECTORWIDGET_H
#define EDITOR_INSPECTORWIDGET_H


#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "src/engine/scene/Entity.h"

class InspectorWidget: public QWidget {
Q_OBJECT;

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
private:
    DeepsEngine::Entity* entitySelected;
    QLabel* entityTagComponentLabel;
public slots:
    void onEntitySelected(DeepsEngine::Entity entity);
};


#endif //EDITOR_INSPECTORWIDGET_H
