//
// Created by Deepak Ramalingam on 3/24/22.
//

#ifndef EDITOR_CAMERACOMPONENTWIDGET_H
#define EDITOR_CAMERACOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class CameraComponentWidget: public ComponentWidget {
    Q_OBJECT;
public:
    explicit CameraComponentWidget(QWidget *parent = nullptr);
    ~CameraComponentWidget();
private:
    DeepsEngine::Component::Camera* cameraComponent;
    // inputs
    QLineEdit* fovInput;
    QLineEdit* zNearInput;
    QLineEdit* zFarInput;

public slots:
    void setComponent(DeepsEngine::Component::Component* camera) override;
    void onFovInputChange();
    void onZNearInputChange();
    void onZFarInputChange();

    std::string getName() override {
        return "Camera";
    }

    void addComponentToEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        // add camera component
        DeepsEngine::Component::Camera camera = {DeepsEngine::Component::Camera({45.0f, 0.1f, 100.0f})};
        entitySelected->AddComponent<DeepsEngine::Component::Camera>(camera);
    }

    bool getComponentFromEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        if (entitySelected->HasComponent<DeepsEngine::Component::Camera>()) {
            this->setVisible(true);
            DeepsEngine::Component::Camera* cameraComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Camera>());
            this->setComponent(cameraComponent);

            return true;
        }

        return false;
    }
};




#endif //EDITOR_CAMERACOMPONENTWIDGET_H
