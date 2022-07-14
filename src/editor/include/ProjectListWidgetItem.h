//
// Created by Deepak Ramalingam on 7/13/22.
//

#ifndef DEEPSENGINE_PROJECTLISTWIDGETITEM_H
#define DEEPSENGINE_PROJECTLISTWIDGETITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDir>

class ProjectListWidgetItem : public QWidget {
Q_OBJECT;
public:
    explicit ProjectListWidgetItem(QWidget *parent = nullptr, QString projectPath = "");
    ~ProjectListWidgetItem();
    QListWidgetItem* getItem();
private:
    QListWidgetItem *item;
};


#endif //DEEPSENGINE_PROJECTLISTWIDGETITEM_H
