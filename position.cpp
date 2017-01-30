//
// Created by johan eriksson on 30/01/2017.
//

#include "headers/position.h"

Position* createPos(){
    Position* position = new Position();
    position->posX = 0;
    position->posY = 4;

    return position;
}

void printPos(Position* p){
    OutputDebugString("Current pos: (" + p->posX + ", " + p->posY + ")");
}

void destroyPosition(Position* p){
    delete[] p;
}

void testPos(){
    Position* p = createPos();

    printPiece(p);
    p->posX = 2;
    p->posY = 3;

    destroyPosition(p);

}
