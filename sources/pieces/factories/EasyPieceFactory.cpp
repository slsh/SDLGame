//
// Created by larsson on 2017-01-31.
//

#include <time.h>
#include <cstdlib>
#include "../../../headers/pieces/factories/EasyPieceFactory.h"
#include "../../../headers/pieces/IPiece.h"
#include "../../../headers/pieces/SquarePiece.h"

EasyPieceFactory::EasyPieceFactory() {
    srand(time(NULL));
    numberOfPieces = 2; // Z S L I T InvertedL Square
}

EasyPieceFactory::~EasyPieceFactory() {
    numberOfPieces = 0;
}

Piece* EasyPieceFactory::getRandomPiece() {
    Piece* p;
    int randomNumber = rand() % numberOfPieces;

    switch (randomNumber) {
        case 0:
            p = new IPiece();
            break;
        case 1:
        default:
            p = new SquarePiece();
    }

    return p;
}