//
// Created by Deepak Ramalingam on 3/21/22.
//

#include "TagComponentWidget.h"
#include "Component.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>

TagComponentWidget::TagComponentWidget(QWidget *parent) {
    this->setVisible(false);

    // get tag component listener
    tagComponentChangeListener = dynamic_cast<TagComponentChangeListener*>(parent);

    if (!tagComponentChangeListener) {
        Logger::Error("Error getting tag component change listener");
        exit(1);
    }

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

void TagComponentWidget::setComponent(DeepsEngine::Component::Component* component) {
    tagComponent = dynamic_cast<DeepsEngine::Component::Tag*>(component);

    if (tagComponent) {
        tagInput->setText(QString::fromStdString(tagComponent->tag));
    }
}

void TagComponentWidget::onTagInputChange() {
    if (tagComponent) {
        tagComponent->tag = tagInput->text().toStdString();

        if (tagComponentChangeListener) {
            tagComponentChangeListener->onTagComponentChange(tagComponent->tag);
        } else {
            Logger::Warn("Tag component change listener not registered");
        }
    }
}