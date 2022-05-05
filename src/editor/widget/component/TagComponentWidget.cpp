//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "TagComponentWidget.h"
#include "Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>

TagComponentWidget::TagComponentWidget(QWidget *parent) {
    // create sample label
    tagInput = new QLineEdit;
    // TODO: add non-empty qvalidator
    tagInput->setPlaceholderText("tag");
    connect(tagInput, SIGNAL(textChanged(const QString &)), this, SLOT(onTagInputChange()));

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Tag"));
    mainLayout->addWidget(tagInput);
    setLayout(mainLayout);
}

TagComponentWidget::~TagComponentWidget() {
    delete tagInput;
}

void TagComponentWidget::setTag(DeepsEngine::Component::Tag* tag) {
    tagComponent = tag;

    if (tagComponent) {
        tagInput->setText(QString::fromStdString(tagComponent->tag));
    }
}

void TagComponentWidget::onTagInputChange() {
    if (tagComponent) {
        tagComponent->tag = tagInput->text().toStdString();

        if (listWidgetItem) {
            this->listWidgetItem->setText(QString::fromStdString(tagComponent->tag));
        }
    }
}

void TagComponentWidget::setListWidgetItem(QListWidgetItem* listWidgetItem) {
    this->listWidgetItem = listWidgetItem;
}
