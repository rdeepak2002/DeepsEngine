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
#include "src/engine/scene/Entity.h"
#include "src/editor/widget/component/TransformComponentWidget.h"
#include "src/editor/widget/component/TagComponentWidget.h"
#include "src/editor/widget/component/MeshFilterComponentWidget.h"

class InspectorWidget: public QWidget {
Q_OBJECT;

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
private:
    std::shared_ptr<DeepsEngine::Entity> entitySelected;
    QPushButton* addComponentButton;
    TagComponentWidget* tagComponentWidget;
    TransformComponentWidget* transformComponentWidget;
    MeshFilterComponentWidget* meshFilterComponentWidget;
    void hideAllComponentWidgets();
    void refresh();

public slots:
    void onEntitySelected(DeepsEngine::Entity entity);
    void onAddComponentMenuClicked(QAction* action);
};


#endif //EDITOR_INSPECTORWIDGET_H
