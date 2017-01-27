//
// Created by larsson on 2017-01-28.
//
/*
 * Class for printing debug messages to standard output.
 *
 * TODO Make this a singelton
 */
#ifndef SDLGAME_DEBUGGER_H
#define SDLGAME_DEBUGGER_H


#include <string>

class Debugger {
private:
    bool debugOn;
public:
    Debugger(bool shouldPrint);
    void outputDebugString(const std::string& s);
};


#endif //SDLGAME_DEBUGGER_H
