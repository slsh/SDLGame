//
// Created by larsson on 2017-01-30.
//

#ifndef SDLGAME_PIECE_H
#define SDLGAME_PIECE_H

#include <vector>
#include <time.h>
#include <cstdlib>
#include <iostream>

class Piece {
protected:
    std::vector<std::vector<std::vector<int>>> representation;
    int rotation;
    int xPosition;
    int yPosition;
public:
    Piece();
    virtual ~Piece()= 0;

    std::vector<std::vector<int>> getNextRotation();
    std::vector<std::vector<int>> getLastRotation();
    std::vector<std::vector<int>> getThisRotation();

    void rotateLeft();
    void rotateRight();

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

    void printPiece();

    void randomizeRotation();// Use after creation of representation
};


#endif //SDLGAME_PIECE_H
