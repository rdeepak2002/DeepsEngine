//
// Created by Deepak Ramalingam on 4/30/22.
//

#ifndef EDITOR_LOGGERCALLBACKINTERFACE_H
#define EDITOR_LOGGERCALLBACKINTERFACE_H

#include <iostream>

class LoggerCallbackInterface
{
public:
    virtual void logCallback (std::string) {};
};

#endif //EDITOR_LOGGERCALLBACKINTERFACE_H
