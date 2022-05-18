//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_INSPECTORWIDGET_H
#define EDITOR_INSPECTORWIDGET_H

#include <QWidget>
#include <QHash>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QPushButton>
#include "Entity.h"
#include "TransformComponentWidget.h"
#include "TagComponentWidget.h"
#include "MeshFilterComponentWidget.h"
#include "CameraComponentWidget.h"
#include "LuaScriptComponentWidget.h"
#include "MaterialComponentWidget.h"
#include "LightComponentWidget.h"

class InspectorWidget: public QWidget, public TagComponentChangeListener {
Q_OBJECT;

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
    void onTagComponentChange(std::string newText) override {
        this->listItem->setText(0, QString::fromStdString(newText));
    }
private:
    std::shared_ptr<DeepsEngine::Entity> entitySelected;
    QPushButton* addComponentButton;
    QPushButton* removeEntityButton;
    QTreeWidgetItem* listItem;
    QList<ComponentWidget*> componentWidgets;
    void hideAllComponentWidgets();
    void refresh();

public slots:
    void onEntitySelected(QHash<QTreeWidgetItem*, std::shared_ptr<DeepsEngine::Entity>> *entityItemMap, QTreeWidgetItem* listItem);
    void onAddComponentMenuClicked(QAction* action);
    void onRemoveEntityButtonClicked();
};


#endif //EDITOR_INSPECTORWIDGET_H
