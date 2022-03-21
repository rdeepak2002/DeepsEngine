//
// Created by Deepak Ramalingam on 3/21/22.
//

#ifndef EDITOR_INSPECTORWIDGET_H
#define EDITOR_INSPECTORWIDGET_H


#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>

class InspectorWidget: public QWidget {
Q_OBJECT;

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();
public slots:
    void onSceneViewItemSelected(QListWidgetItem* item);
};


#endif //EDITOR_INSPECTORWIDGET_H
