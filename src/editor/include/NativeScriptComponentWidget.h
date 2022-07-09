//
// Created by Deepak Ramalingam on 6/26/22.
//

#ifndef DEEPSENGINE_NATIVESCRIPTCOMPONENTWIDGET_H
#define DEEPSENGINE_NATIVESCRIPTCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QLineEdit>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"
#include "FileSelectWidget.h"

class NativeScriptComponentWidget: public ComponentWidget {
Q_OBJECT;
public:
    explicit NativeScriptComponentWidget(QWidget *parent = nullptr);
    ~NativeScriptComponentWidget();
private:
    DeepsEngine::Component::NativeScriptComponent* nativeScriptComponent;
    FileSelectWidget* fileSelectWidget;

public slots:
    void onFileSelected(std::string relativeFilePath, std::string absoluteFilePath);
    void openFile(std::string relativeFilePath, std::string absoluteFilePath);

    void setComponent(DeepsEngine::Component::Component* component) override;

    std::string getName() override {
        return "NativeScript";
    }

    void addComponentToEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        // add tag component
        DeepsEngine::Component::NativeScriptComponent spinningEntity = {"", ""};
        entitySelected->AddComponent<DeepsEngine::Component::NativeScriptComponent>(spinningEntity);
    }

    bool getComponentFromEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        if (entitySelected->HasComponent<DeepsEngine::Component::NativeScriptComponent>()) {
            this->setVisible(true);
            DeepsEngine::Component::NativeScriptComponent* nativeScriptComponent = &(entitySelected->GetComponent<DeepsEngine::Component::NativeScriptComponent>());
            this->setComponent(nativeScriptComponent);

            return true;
        }

        return false;
    }
};


#endif //DEEPSENGINE_NATIVESCRIPTCOMPONENTWIDGET_H
