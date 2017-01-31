//
// Created by larsson on 2017-01-30.
//

#ifndef SDLGAME_PIECEFACTORY_H
#define SDLGAME_PIECEFACTORY_H

#include "Pieces/Piece.h"

class PieceFactory {
public:
    virtual Piece* getRandomPiece()= 0;
};

#endif //SDLGAME_PIECEFACTORY_H
