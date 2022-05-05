//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_MESHFILTERCOMPONENT_H
#define EDITOR_MESHFILTERCOMPONENT_H


#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "src/engine/header/Entity.h"
#include "src/engine/header/Component.h"

class MeshFilterComponentWidget: public QWidget {
Q_OBJECT;
public:
    explicit MeshFilterComponentWidget(QWidget *parent = nullptr);
    ~MeshFilterComponentWidget();
private:
    QLabel* meshFilterLabel;
    DeepsEngine::Component::MeshFilter* meshFilterComponent;

public slots:
    void setMeshFilter(DeepsEngine::Component::MeshFilter* meshFilter);
};


#endif //EDITOR_MESHFILTERCOMPONENT_H
