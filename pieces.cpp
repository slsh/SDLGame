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

//Constructor
Pieces::Pieces() {
    pieceName = Pieces::randomisePiece();
    posX = 0;
    posY = 4;
    rotation = Pieces::randomiseRotation();

    //Expand the vectors
    for (int k = 0; k < 4; ++k) {
        thisPiece.push_back(std::vector<int>());
        nextPiece.push_back(std::vector<int>());
    }

    //Copy data to the vectors
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            thisPiece[i].push_back( g_piece_database[pieceName][rotation][i][j] );
            nextPiece[i].push_back( g_piece_database[pieceName][rotation][i][j] );
        }

    }
}

Pieces::~Pieces(){
    thisPiece.clear();
    nextPiece.clear();
}

//Rotate the piece
void Pieces::rotatePiece(Pieces* p){
    if (p->rotation == 3){
        p->rotation = 0;
    } else{
        p->rotation++;
    }
    //std::copy(&p->nextPiece[0][0], &p->nextPiece[0][0] + 4 * 4, &p->thisPiece[0][0]);
    //std::copy(&g_piece_database[p->pieceName][p->rotation][0][0], &g_piece_database[p->pieceName][p->rotation][0][0] + 4 * 4, &p->nextPiece[0][0]);
}

//Update rotation
int Pieces::updatePiece(Pieces* p, int rotation){
    if (rotationVerifier(rotation)){
        return g_piece_database[p->pieceName][rotation][0][0];
    }
    return NULL;
}

//Print piece to console
void Pieces::printPiece(Pieces* p){
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

bool Pieces::rotationVerifier(int rotation){
    if (rotation < 0 || rotation > 3){
        return false;
    }
    return true;
}


PieceID Pieces::randomisePiece(){
    PieceID randomPieceValue = static_cast<PieceID>(rand() % G_PIECE_COUNT);
    return randomPieceValue;
}

int Pieces::randomiseRotation(){
    return rand() % 4;
}

void Pieces::testPiece() {
    Pieces* p = new Pieces();
    Pieces* p2 = new Pieces();

    std::cout << "\nPrint piece 1" << std::endl;
    printPiece(p);

    std::cout << "\nPrint piece 2" << std::endl;
    printPiece(p2);

    delete p;
    delete p2;

}

