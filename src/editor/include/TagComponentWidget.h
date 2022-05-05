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

class TagComponentWidget: public QWidget {
Q_OBJECT;
public:
    explicit TagComponentWidget(QWidget *parent = nullptr);
    ~TagComponentWidget();
private:
    DeepsEngine::Component::Tag* tagComponent;
    // inputs
    QLineEdit* tagInput;
    QListWidgetItem* listWidgetItem;

public slots:
    void setTag(DeepsEngine::Component::Tag* tag);
    void onTagInputChange();
    void setListWidgetItem(QListWidgetItem* listWidgetItem);
};

#endif //EDITOR_TAGCOMPONENTWIDGET_H