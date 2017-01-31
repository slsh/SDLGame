//
// Created by larsson on 2017-01-31.
//

#include <time.h>
#include <cstdlib>
#include "../../../headers/pieces/factories/StandardPieceFactory.h"
#include "../../../headers/pieces/ZPiece.h"
#include "../../../headers/pieces/SPiece.h"
#include "../../../headers/pieces/LPiece.h"
#include "../../../headers/pieces/InvertedLPiece.h"
#include "../../../headers/pieces/IPiece.h"
#include "../../../headers/pieces/TPiece.h"
#include "../../../headers/pieces/SquarePiece.h"

StandardPieceFactory::StandardPieceFactory() {
    srand(time(NULL));
    numberOfPieces = 7; // Z S L I T InvertedL Square
}

StandardPieceFactory::~StandardPieceFactory() {
    numberOfPieces = 0;
}

Piece* StandardPieceFactory::getRandomPiece() {
    Piece* p;
    int randomNumber = rand() % numberOfPieces;

    switch (randomNumber) {
        case 0:
            p = new ZPiece();
            break;
        case 1:
            p = new SPiece();
            break;
        case 2:
            p = new LPiece();
            break;
        case 3:
            p = new InvertedLPiece();
            break;
        case 4:
            p = new IPiece();
            break;
        case 5:
            p = new TPiece();
            break;
        case 6:
        default:
            p = new SquarePiece();
    }

    return p;
}