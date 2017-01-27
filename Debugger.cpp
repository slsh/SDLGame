//
// Created by larsson on 2017-01-28.
//

#include <iostream>
#include "headers/Debugger.h"

Debugger::Debugger(bool shouldPrint) {
    this->debugOn = shouldPrint;
}

void Debugger::outputDebugString(const std::string& s) {
    if (this->debugOn) {
        std::cout << s << std::endl;
    }
}