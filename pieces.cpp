//
// Created by johan eriksson on 26/01/2017.
//

#include "headers\pieces.h"
#include <windows.h>
#include "headers\pieceDatabase.h"
#include <ctime>

/*
	Variablar
PieceID pieceName;
Direction direction;
int posX;
int posY;
int rotation;

int thisPiece[4][4];
int nextPiece[4][4];

int leftEdge;
int rightEdge;

*/

Pieces* createPiece(){
    Pieces* piece = new Pieces;
    piece->pieceName = randomisePiece();
    piece->posX = 0;
    piece->posY = 4;
    piece->rotation = randomiseRotation();
    //Compilern gnäller på std::copy - byt till forloop
    // Byt ut lång string mot den kortare vid senare tillfälle
    //std::copy(updatePiece(piece, rotation), updatePiece(piece, rotation) + 4 * 4, &piece->thisPiece[0][0]);
    std::copy(&g_piece_database[piece->pieceName][piece->rotation][0][0], &g_piece_database[piece->pieceName][piece->rotation][0][0] + 4 * 4, &piece->thisPiece[0][0]);
    std::copy(&g_piece_database[piece->pieceName][piece->rotation][0][0], &g_piece_database[piece->pieceName][piece->rotation][0][0] + 4 * 4, &piece->nextPiece[0][0]);
    //	std::copy(&myint[0][0], &myint[0][0] + rows*columns, &favint[0][0]);

    return piece;
}

void destroyPiece(Pieces* p){
    delete[] p;
}

//Rotate the piece
void rotatePiece(Pieces* p){
    if (p->rotation == 3){
        p->rotation = 0;
    } else{
        p->rotation++;
    }
    std::copy(&p->nextPiece[0][0], &p->nextPiece[0][0] + 4 * 4, &p->thisPiece[0][0]);
    std::copy(&g_piece_database[p->pieceName][p->rotation][0][0], &g_piece_database[p->pieceName][p->rotation][0][0] + 4 * 4, &p->nextPiece[0][0]);
}

//Update rotation
int updatePiece(Pieces* p, int rotation){
    if (rotationVerifier(rotation)){
        return g_piece_database[p->pieceName][rotation][0][0];
    }
    return NULL;
}

//Console print
void printPiece(Pieces* p){
    for (int i = 0; i < 4; ++i){
        OutputDebugString("\n");
        for (int j = 0; j < 4; ++j){
            if (p->thisPiece[i][j] == 1){
                OutputDebugString("1,");
            } else{
                OutputDebugString("0,");
            }
        }
    }
}

bool rotationVerifier(int rotation){
    if (rotation < 0 || rotation > 3){
        return false;
    }
    return true;
}


PieceID randomisePiece(){
    srand(time(0));
    PieceID randomPieceValue = static_cast<PieceID>(rand() % G_PIECE_COUNT);
    return randomPieceValue;
}

int randomiseRotation(){
    return rand() % 4;
}

void testPiece() {
    Pieces* p = createPiece();
    Pieces* p2 = createPiece();

    printPiece(p);
    printPiece(p2);

    destroyPiece(p);
    destroyPiece(p2);
}

