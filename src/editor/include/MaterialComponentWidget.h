//
// Created by Deepak Ramalingam on 5/13/22.
//

#ifndef DEEPSENGINE_MATERIALCOMPONENTWIDGET_H
#define DEEPSENGINE_MATERIALCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QLineEdit>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class MaterialComponentWidget: public ComponentWidget {
Q_OBJECT;
public:
    explicit MaterialComponentWidget(QWidget *parent = nullptr);
    ~MaterialComponentWidget();
private:
    DeepsEngine::Component::Material* materialComponent;
    QLabel* diffuseTexturePathLabel;
    QLabel* specularTexturePathLabel;
    QLineEdit* shininessLineEdit;

public slots:
    void onShininessInputChange();

    void setComponent(DeepsEngine::Component::Component* component) override;

    std::string getName() override {
        return "Material";
    }

    void addComponentToEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        // add tag component
        DeepsEngine::Component::Material material = {"src/textures/container2.png", "src/textures/container2_specular.png", 32.0f};
        entitySelected->AddComponent<DeepsEngine::Component::Material>(material);
    }

    bool getComponentFromEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        if (entitySelected->HasComponent<DeepsEngine::Component::Material>()) {
            this->setVisible(true);
            DeepsEngine::Component::Material* materialComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Material>());
            this->setComponent(materialComponent);

            return true;
        }

        return false;
    }
};


#endif //DEEPSENGINE_MATERIALCOMPONENTWIDGET_H
