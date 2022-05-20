//
// Created by Deepak Ramalingam on 5/20/22.
//

#include "ClickableLabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}