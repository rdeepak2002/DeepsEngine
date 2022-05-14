//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_TAGCOMPONENTWIDGET_H
#define EDITOR_TAGCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QLineEdit>
#include "Entity.h"
#include "Component.h"
#include "ComponentWidget.h"
#include "TagComponentChangeListener.h"

class TagComponentWidget: public ComponentWidget {
Q_OBJECT;
public:
    explicit TagComponentWidget(QWidget *parent = nullptr);
    ~TagComponentWidget();
private:
    DeepsEngine::Component::Tag* tagComponent;
    // inputs
    QLineEdit* tagInput;
    TagComponentChangeListener* tagComponentChangeListener;

public slots:
    void setComponent(DeepsEngine::Component::Component* component) override;

    std::string getName() override {
        return "Tag";
    }

    void onTagInputChange();

    void addComponentToEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        // add tag component
        DeepsEngine::Component::Tag tag = {"entity"};
        entitySelected->AddComponent<DeepsEngine::Component::Tag>(tag);
    }

    bool getComponentFromEntity(std::shared_ptr<DeepsEngine::Entity> entitySelected) override {
        if (entitySelected->HasComponent<DeepsEngine::Component::Tag>()) {
            this->setVisible(true);
            DeepsEngine::Component::Tag* tagComponent = &(entitySelected->GetComponent<DeepsEngine::Component::Tag>());
            this->setComponent(tagComponent);

            return true;
        }

        return false;
    }
};

#endif //EDITOR_TAGCOMPONENTWIDGET_H
