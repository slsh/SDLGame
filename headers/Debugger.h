//
// Created by larsson on 2017-01-28.
//

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
