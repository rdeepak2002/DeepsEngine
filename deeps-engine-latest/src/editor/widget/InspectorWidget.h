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

class InspectorWidget: public QWidget {
Q_OBJECT;

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
private:
    std::shared_ptr<DeepsEngine::Entity> entitySelected;
    QLabel* entityTagComponentLabel;
    // TODO: encapsulate this into general transform qt widget
    QLineEdit* transformPositionXInput;

public slots:
    void onEntitySelected(DeepsEngine::Entity entity);
    void onTransformPositionXInputChange();
};


#endif //EDITOR_INSPECTORWIDGET_H
