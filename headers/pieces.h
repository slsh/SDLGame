//
// Created by johan eriksson on 26/01/2017.
//

#ifndef SDLGAME_PIECES_H
#define SDLGAME_PIECES_H

#endif //SDLGAME_PIECES_H

// Constant for pieces
enum PieceID{
    G_PIECE_I,
    G_PIECE_O,
    G_PIECE_T,
    G_PIECE_S,
    G_PIECE_Z,
    G_PIECE_L,
    G_PIECE_IL,
    G_PIECE_COUNT
};

// Constant for directions
enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ROTATE
};


//Struct for pieces
struct Pieces{
    PieceID pieceName;
    Direction direction;
    int posX;
    int posY;
    int rotation;

    int thisPiece[4][4];
    int nextPiece[4][4];

    int leftEdge;
    int rightEdge;
};

//Prototypes
Pieces* createPiece();
void destroyPiece(Pieces* p);

int updatePiece(Pieces* p, int rotation);
void rotatePiece(Pieces* p);
bool rotationVerifier(int rotation);
PieceID randomisePiece();
int randomiseRotation();

void testPiece();
void printPiece(Pieces* p);