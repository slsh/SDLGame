//
// Created by johan eriksson on 30/01/2017.
//

#ifndef SDLGAME_POSITION_H
#define SDLGAME_POSITION_H

struct Position{
    int posX;
    int posY;
};

Position* createPos();
Position getPos();
void testPos();
void printPos(Position* p);
void destroyPosition(Position* p);

#endif //SDLGAME_POSITION_H

