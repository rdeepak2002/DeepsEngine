//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_MESHFILTERCOMPONENT_H
#define EDITOR_MESHFILTERCOMPONENT_H


#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class MeshFilterComponentWidget: public ComponentWidget {
Q_OBJECT;
public:
    explicit MeshFilterComponentWidget(QWidget *parent = nullptr);
    ~MeshFilterComponentWidget();
private:
    QLabel* meshFilterLabel;
    DeepsEngine::Component::MeshFilter* meshFilterComponent;

public slots:
    void setComponent(DeepsEngine::Component::Component* component) override;

    std::string getName() override {
        return "Mesh Filter";
    }
};


#endif //EDITOR_MESHFILTERCOMPONENT_H
