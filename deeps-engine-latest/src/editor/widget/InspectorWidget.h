//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_INSPECTORWIDGET_H
#define EDITOR_INSPECTORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "src/engine/scene/Entity.h"
#include "src/editor/widget/component/TransformComponentWidget.h"
#include "src/editor/widget/component/TagComponentWidget.h"

class InspectorWidget: public QWidget {
Q_OBJECT;

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
private:
    std::shared_ptr<DeepsEngine::Entity> entitySelected;
    QLabel* inspectorTitle;
    TagComponentWidget* tagComponentWidget;
    TransformComponentWidget* transformComponentWidget;
    void hideAllComponentWidgets();

public slots:
    void onEntitySelected(DeepsEngine::Entity entity);
};


#endif //EDITOR_INSPECTORWIDGET_H
