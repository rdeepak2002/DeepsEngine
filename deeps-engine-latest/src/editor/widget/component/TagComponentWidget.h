//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_TAGCOMPONENTWIDGET_H
#define EDITOR_TAGCOMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include "src/engine/scene/Entity.h"
#include "src/engine/component/Component.h"

class TagComponentWidget: public QWidget {
Q_OBJECT;
public:
    explicit TagComponentWidget(QWidget *parent = nullptr);
    ~TagComponentWidget();
private:
    QLabel* tagLabel;
    DeepsEngine::Component::Tag* tagComponent;

public slots:
    void setTag(DeepsEngine::Component::Tag* tag);
};

#endif //EDITOR_TAGCOMPONENTWIDGET_H
