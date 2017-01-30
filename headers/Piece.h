//
// Created by larsson on 2017-01-30.
//

#ifndef SDLGAME_PIECE_H
#define SDLGAME_PIECE_H

#include <vector>

class Piece {
protected:
    std::vector<std::vector<std::vector<int>>> representation;
    int rotation;
    int xPosition;
    int yPosition;
public:
    virtual Piece()= 0;
    virtual ~Piece()= 0;
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
};


#endif //SDLGAME_PIECE_H
