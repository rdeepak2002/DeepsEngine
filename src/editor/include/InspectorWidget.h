//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_INSPECTORWIDGET_H
#define EDITOR_INSPECTORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include "Entity.h"
#include "TransformComponentWidget.h"
#include "TagComponentWidget.h"
#include "MeshFilterComponentWidget.h"
#include "CameraComponentWidget.h"

class InspectorWidget: public QWidget {
Q_OBJECT;

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
private:
    std::shared_ptr<DeepsEngine::Entity> entitySelected;
    QPushButton* addComponentButton;
    QPushButton* removeEntityButton;
    TagComponentWidget* tagComponentWidget;
    TransformComponentWidget* transformComponentWidget;
    CameraComponentWidget* cameraComponentWidget;
    MeshFilterComponentWidget* meshFilterComponentWidget;
    QListWidgetItem* listItem;
    void hideAllComponentWidgets();
    void refresh();

public slots:
    void onEntitySelected(DeepsEngine::Entity entity, QListWidgetItem* listItem);
    void onAddComponentMenuClicked(QAction* action);
    void onRemoveEntityButtonClicked();
};


#endif //EDITOR_INSPECTORWIDGET_H
