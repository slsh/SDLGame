//
// Created by johan eriksson on 26/01/2017.
//



#include "headers/pieces.h"
//#include <windows.h>
#include <ctime>
#include "headers/pieceDatabase.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

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

    //Expand the vectors
    for (int k = 0; k < 4; ++k) {
        piece->thisPiece.push_back(std::vector<int>());
        piece->nextPiece.push_back(std::vector<int>());
    }

    //Copy data to the vectors
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            piece->thisPiece[i].push_back( g_piece_database[piece->pieceName][piece->rotation][i][j] );
            piece->nextPiece[i].push_back( g_piece_database[piece->pieceName][piece->rotation][i][j] );
        }

    }
    return piece;
}

void destroyPiece(Pieces* p){
    delete p;

}

//Rotate the piece
void rotatePiece(Pieces* p){
    if (p->rotation == 3){
        p->rotation = 0;
    } else{
        p->rotation++;
    }
    //std::copy(&p->nextPiece[0][0], &p->nextPiece[0][0] + 4 * 4, &p->thisPiece[0][0]);
    //std::copy(&g_piece_database[p->pieceName][p->rotation][0][0], &g_piece_database[p->pieceName][p->rotation][0][0] + 4 * 4, &p->nextPiece[0][0]);
}

//Update rotation
int updatePiece(Pieces* p, int rotation){
    if (rotationVerifier(rotation)){
        return g_piece_database[p->pieceName][rotation][0][0];
    }
    return NULL;
}

//Print piece to console
void printPiece(Pieces* p){
    for (int i = 0; i < 4; ++i){
        std::cout << std::endl;
        for (int j = 0; j < 4; ++j){
            if (p->thisPiece[i][j] > 0){
                std::cout << ("1");
            } else {
                std::cout << ("0");
            }
        }

    }
    std::cout << std::endl;
}

bool rotationVerifier(int rotation){
    if (rotation < 0 || rotation > 3){
        return false;
    }
    return true;
}


PieceID randomisePiece(){
    PieceID randomPieceValue = static_cast<PieceID>(rand() % G_PIECE_COUNT);
    return randomPieceValue;
}

int randomiseRotation(){
    return rand() % 4;
}

void testPiece() {
    Pieces* p = createPiece();
    Pieces* p2 = createPiece();

    std::cout << "\nPrint piece 1" << std::endl;
    printPiece(p);

    std::cout << "\nPrint piece 2" << std::endl;
    printPiece(p2);

    destroyPiece(p);
    destroyPiece(p2);

}

