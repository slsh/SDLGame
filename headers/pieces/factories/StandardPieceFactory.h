//
// Created by larsson on 2017-01-31.
//

#ifndef SDLGAME_STANDARDPIECEFACTORY_H
#define SDLGAME_STANDARDPIECEFACTORY_H

#include "PieceFactory.h"

class StandardPieceFactory: public PieceFactory {
private:
    int numberOfPieces;
public:
    StandardPieceFactory();
    ~StandardPieceFactory();
    Piece* getRandomPiece();
};

#endif //SDLGAME_STANDARDPIECEFACTORY_H
