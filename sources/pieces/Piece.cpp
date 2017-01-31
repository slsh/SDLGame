//
// Created by larsson on 2017-01-31.
//

#include "../../headers/pieces/Piece.h"

Piece::Piece() {
    srand(time(NULL));
    rotation = 0;
    xPosition = 0;
    yPosition = 0;
}

Piece::~Piece() {
    representation.clear();
}

int Piece::getX() {
    return xPosition;
}

int Piece::getY() {
    return yPosition;
}

void Piece::setX(int x) {
    xPosition = x;
}
void Piece::setY(int y) {
    yPosition = y;
}

void Piece::printPiece() {
    for (std::vector<int> row : getThisRotation()) {
        for (int val : row) {
            std::cout << val;
        }
        std::cout << std::endl;
    }
}

void Piece::randomizeRotation() {
    rotation = rand() % (int)representation.size();
}

std::vector<std::vector<int>> Piece::getNextRotation() {
    return representation[(rotation+1) % representation.size()];
}

std::vector<std::vector<int>> Piece::getLastRotation() {
    return representation[(rotation-1) % representation.size()];
}

std::vector<std::vector<int>> Piece::getThisRotation() {
    return representation[rotation];
}

void Piece::rotateLeft() {

    rotation = (rotation - 1) % (int)representation.size();
    if(rotation < 0){ rotation = ((int)representation.size() -1 );} // -1 not acceptable as vector id

}
void Piece::rotateRight() {
    rotation = (rotation + 1) % (int)representation.size();

}