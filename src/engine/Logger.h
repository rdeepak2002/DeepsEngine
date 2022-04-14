//
// Created by Deepak Ramalingam on 3/24/22.
//

#ifndef EDITOR_LOGGER_H
#define EDITOR_LOGGER_H

#if !defined(STANDALONE)
#include "src/editor/widget/ConsoleWidget.h"
#endif

#include <iostream>

class Logger {
public:
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    static void Debug(std::string text) {
        std::string formattedText = "DEBUG: " + text;
        SendLogToEditor(formattedText);
        printf("%s\n", formattedText.c_str());
    }

    static void Error(std::string text) {
        std::string formattedText = "ERROR: " + text;
        SendLogToEditor(formattedText);
        printf("%s\n", formattedText.c_str());
    }

    static int SendLogToEditor(std::string text) {
#if !defined(STANDALONE)
        if (Logger::getInstance().consoleWidget) {
            Logger::getInstance().consoleWidget->logCallback(text);
            return 1;
        }
#endif
        return 0;
    }

#if !defined(STANDALONE)
    static void setConsoleWidget(ConsoleWidget* consoleWidget) {
        Logger::getInstance().consoleWidget = nullptr;
        Logger::getInstance().consoleWidget = consoleWidget;
    }
#endif
private:
#if !defined(STANDALONE)
    ConsoleWidget* consoleWidget;
#endif
};


#endif //EDITOR_LOGGER_H
