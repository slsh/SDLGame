//
// Created by larsson on 2017-01-31.
// Use this for debugging - it's not fun for real play!

#ifndef SDLGAME_EASYPIECEFACTORY_H
#define SDLGAME_EASYPIECEFACTORY_H

#include "PieceFactory.h"

class EasyPieceFactory: public PieceFactory {
private:
    int numberOfPieces;
public:
    EasyPieceFactory();
    ~EasyPieceFactory();
    Piece* getRandomPiece();
};

#endif //SDLGAME_EASYPIECEFACTORY_H
