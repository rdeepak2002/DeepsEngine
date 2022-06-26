//
// Created by Deepak Ramalingam on 3/24/22.
//

#ifndef EDITOR_LOGGER_H
#define EDITOR_LOGGER_H

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#include <iostream>
#include "LoggerCallbackInterface.h"

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
#if defined(EMSCRIPTEN)
        printf("%s\n", formattedText.c_str());
#else
        printf("%s%s%s\n", KBLU, formattedText.c_str(), KNRM);
#endif
    }

    static void Error(std::string text) {
        std::string formattedText = "ERROR: " + text;
        SendLogToEditor(formattedText);
#if defined(EMSCRIPTEN)
        printf("%s\n", formattedText.c_str());
#else
        printf("%s%s%s\n", KRED, formattedText.c_str(), KNRM);
#endif
    }

    static void Warn(std::string text) {
        std::string formattedText = "WARNING: " + text;
        SendLogToEditor(formattedText);
#if defined(EMSCRIPTEN)
        printf("%s\n", formattedText.c_str());
#else
        printf("%s%s%s\n", KYEL, formattedText.c_str(), KNRM);
#endif
    }

    static int SendLogToEditor(std::string text) {
        if (Logger::getInstance().consoleWidget) {
            Logger::getInstance().consoleWidget->logCallback(text);
            return 1;
        }

        return 0;
    }

    static void setConsoleWidget(LoggerCallbackInterface* consoleWidget) {
        Logger::getInstance().consoleWidget = nullptr;
        Logger::getInstance().consoleWidget = consoleWidget;
    }
private:
    Logger() {}
    LoggerCallbackInterface* consoleWidget;
public:
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;
};


#endif //EDITOR_LOGGER_H
