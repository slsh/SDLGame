//
// Created by larsson on 2017-01-30.
//
#ifndef SDLGAME_IPIECE_H
#define SDLGAME_IPIECE_H

#include "Piece.h"

class IPiece:public Piece {
public:
    IPiece();
    ~IPiece(); // This has to be declared
};

#endif //SDLGAME_IPIECE_H