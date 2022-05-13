//
// Created by Deepak Ramalingam on 5/13/22.
//

#ifndef DEEPSENGINE_TAGCOMPONENTCHANGELISTENER_H
#define DEEPSENGINE_TAGCOMPONENTCHANGELISTENER_H

#include <stdio.h>
#include <string>
#include "Logger.h"

class TagComponentChangeListener {
public:
    virtual void onTagComponentChange(std::string newText) {
        Logger::Error("Method not implemented");
        exit(1);
    }
};

#endif //DEEPSENGINE_TAGCOMPONENTCHANGELISTENER_H
