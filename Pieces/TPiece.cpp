//
// Created by larsson on 2017-01-30.
//

#include <iostream>
#include "../headers/Pieces/TPiece.h"

TPiece::TPiece() {
    representation =
        {
            {
                { 0, 3, 0, 0 },
                { 3, 3, 3, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 3, 0, 0 },
                { 0, 3, 3, 0 },
                { 0, 3, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 0, 0, 0 },
                { 3, 3, 3, 0 },
                { 0, 3, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 3, 0, 0 },
                { 3, 3, 0, 0 },
                { 0, 3, 0, 0 },
                { 0, 0, 0, 0 }
            }
        };
    randomizeRotation();
}


std::vector<std::vector<int>> TPiece::getNextRotation() {
    return representation[(rotation+1) % representation.size()];
}

std::vector<std::vector<int>> TPiece::getLastRotation() {
    return representation[(rotation-1) % representation.size()];
}

std::vector<std::vector<int>> TPiece::getThisRotation() {
    return representation[rotation];
}

void TPiece::rotateLeft() {
    rotation = (rotation - 1) % (int)representation.size();
}
void TPiece::rotateRight() {
    rotation = (rotation + 1) % (int)representation.size();
}