//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_TRANSFORMCOMPONENTWIDGET_H
#define EDITOR_TRANSFORMCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class TransformComponentWidget: public ComponentWidget {
Q_OBJECT;
public:
    explicit TransformComponentWidget(QWidget *parent = nullptr);
    ~TransformComponentWidget();
private:
    // reference to the transform being displayed
    DeepsEngine::Component::Transform* transformComponent;

    // position inputs
    QLineEdit* positionXInput;
    QLineEdit* positionYInput;
    QLineEdit* positionZInput;

    // rotation inputs
    QLineEdit* rotationXInput;
    QLineEdit* rotationYInput;
    QLineEdit* rotationZInput;

    // scale inputs
    QLineEdit* scaleXInput;
    QLineEdit* scaleYInput;
    QLineEdit* scaleZInput;

public slots:
    void setComponent(DeepsEngine::Component::Component* component) override;

    void onPositionXInputChange();
    void onPositionYInputChange();
    void onPositionZInputChange();

    void onRotationXInputChange();
    void onRotationYInputChange();
    void onRotationZInputChange();

    void onScaleXInputChange();
    void onScaleYInputChange();
    void onScaleZInputChange();

    std::string getName() override {
        return "Transform";
    }

    void addComponentToEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        // add transform component
        DeepsEngine::Component::Transform transform = {glm::vec3(0, 0, 0),
                                                       glm::vec3(0, 0, 0),
                                                       glm::vec3(1, 1, 1)};
        entitySelected->AddComponent<DeepsEngine::Component::Transform>(transform);
    }

    bool getComponentFromEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        if (entitySelected->HasComponent<DeepsEngine::Component::Transform>()) {
            this->setVisible(true);
            DeepsEngine::Component::Transform* transformComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Transform>());
            this->setComponent(transformComponent);

            return true;
        }

        return false;
    }
};


#endif //EDITOR_TRANSFORMCOMPONENTWIDGET_H
