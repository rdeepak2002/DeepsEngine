//
// Created by Deepak Ramalingam on 5/20/22.
//

#ifndef DEEPSENGINE_CLICKABLELABEL_H
#define DEEPSENGINE_CLICKABLELABEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>

class ClickableLabel: public QLabel {
Q_OBJECT;
signals:
    void clicked();
public:
    void mousePressEvent(QMouseEvent* event);
    using QLabel::QLabel;
};


#endif //DEEPSENGINE_CLICKABLELABEL_H
