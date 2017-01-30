//
// Created by larsson on 2017-01-30.
//

#include <iostream>
#include "../Piece.h"

class TPiece:public Piece {
public:
    TPiece();
    std::vector<std::vector<int>> getNextRotation();
    std::vector<std::vector<int>> getLastRotation();
    std::vector<std::vector<int>> getThisRotation();
    void rotateLeft();
    void rotateRight();
};