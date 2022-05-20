//
// Created by Deepak Ramalingam on 5/13/22.
//

#ifndef DEEPSENGINE_LUASCRIPTCOMPONENTWIDGET_H
#define DEEPSENGINE_LUASCRIPTCOMPONENTWIDGET_H

#include "FileSelectWidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"

class LuaScriptComponentWidget: public ComponentWidget {
Q_OBJECT;
public:
    explicit LuaScriptComponentWidget(QWidget *parent = nullptr);
    ~LuaScriptComponentWidget();
private:
    DeepsEngine::Component::LuaScript* luaScriptComponent;
    FileSelectWidget* fileSelectWidget;

public slots:
    void onFileSelected(std::string);

    void setComponent(DeepsEngine::Component::Component* component) override;

    std::string getName() override {
        return "Lua Script";
    }

    void addComponentToEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        // add tag component
        DeepsEngine::Component::LuaScript luaScript = {""};
        entitySelected->AddComponent<DeepsEngine::Component::LuaScript>(luaScript);
    }

    bool getComponentFromEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        if (entitySelected->HasComponent<DeepsEngine::Component::LuaScript>()) {
            this->setVisible(true);
            DeepsEngine::Component::LuaScript* luaScriptComponent = &(entitySelected->GetComponent<DeepsEngine::Component::LuaScript>());
            this->setComponent(luaScriptComponent);

            return true;
        }

        return false;
    }
};


#endif //DEEPSENGINE_LUASCRIPTCOMPONENTWIDGET_H
