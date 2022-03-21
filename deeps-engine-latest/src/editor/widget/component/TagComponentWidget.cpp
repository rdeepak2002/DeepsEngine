//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "TagComponentWidget.h"
#include "src/engine/component/Component.h"
#include <iostream>
#include <QLabel>

TagComponentWidget::TagComponentWidget(QWidget *parent) {
    // create sample label
    tagLabel = new QLabel("None");

    // add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Tag"));
    mainLayout->addWidget(tagLabel);
    setLayout(mainLayout);
}

TagComponentWidget::~TagComponentWidget() {
    delete tagLabel;
}

void TagComponentWidget::setTag(DeepsEngine::Component::Tag* tag) {
    tagComponent = tag;

    if (tagComponent) {
        tagLabel->setText(QString::fromStdString(tagComponent->tag));
    }
}
