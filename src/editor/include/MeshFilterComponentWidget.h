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

    void addComponentToEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        // add mesh filter component
        DeepsEngine::Component::MeshFilter cubeMeshFilter = {"cube"};
        entitySelected->AddComponent<DeepsEngine::Component::MeshFilter>(cubeMeshFilter);
    }

    bool getComponentFromEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        if (entitySelected->HasComponent<DeepsEngine::Component::MeshFilter>()) {
            this->setVisible(true);
            DeepsEngine::Component::MeshFilter* meshFilterComponent = &(entitySelected->GetComponent<DeepsEngine::Component::MeshFilter>());
            this->setComponent(meshFilterComponent);

            return true;
        }

        return false;
    }
};


#endif //EDITOR_MESHFILTERCOMPONENT_H
