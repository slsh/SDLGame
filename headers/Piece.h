//
// Created by larsson on 2017-01-30.
//

#ifndef SDLGAME_PIECE_H
#define SDLGAME_PIECE_H

#include <vector>
#include <time.h>

class Piece {
protected:
    std::vector<std::vector<std::vector<int>>> representation;
    int rotation;
    int xPosition;
    int yPosition;
public:
    Piece() {
        srand(time(NULL));
        rotation = 0;
        xPosition = 0;
        yPosition = 0;
    }
    ~Piece() {
        representation.clear();
    }
    virtual std::vector<std::vector<int>> getNextRotation()= 0;
    virtual std::vector<std::vector<int>> getLastRotation()= 0;
    virtual std::vector<std::vector<int>> getThisRotation()= 0;
    virtual void rotateLeft()= 0;
    virtual void rotateRight()= 0;
    int getX() {
        return xPosition;
    }
    int getY() {
        return yPosition;
    }
    void setX(int x) {
        xPosition = x;
    }
    void setY(int y) {
        yPosition = y;
    }
    void printPiece() {
        for (std::vector<int> row : getThisRotation()) {
            for (int val : row) {
                std::cout << val;
            }
            std::cout << std::endl;
        }
    }

    // Use after creation of representation
    void randomizeRotation() {
        rotation = rand() % (int)representation.size();
    }
};


#endif //SDLGAME_PIECE_H
