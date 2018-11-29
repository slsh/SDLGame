//
// Created by johan eriksson on 31/01/2017.
//

#ifndef SDLGAME_GAME_H
#define SDLGAME_GAME_H

#include <SDL2/SDL.h>

#include <iostream>
#include "timer.h"
#include "Debugger.h"

#include "pieces/factories/PieceFactory.h"
#include "pieces/factories/StandardPieceFactory.h"
#include "pieces/factories/EasyPieceFactory.h"
#include "Colors.h"

class Game {
public:
    enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ROTATE
    };

    Game();
    ~Game() {}

    //Prototypes
    void init();
    void updateKey(SDL_KeyboardEvent *key);
    void movePiece(Direction direction);
//    void updateWindow();
    void close();
    // a function to access the private running variable
    bool isRunning() { return gameRunning; }
    bool isPaused() { return pauseCheck; }
    bool isGameOver() {return gameOver; }

    unsigned long long getHighScore();
    unsigned long long getScore();
    short getSpeed();
    std::vector<std::vector<int>> currentLevel;

    Piece* getCurrentPiece();
    Piece* getNextPiece();

private:
    unsigned const int LEVELROW = 24;
    unsigned const int LEVELCOL = 12;
    bool gameRunning;
    bool pauseCheck;
    bool gameOver;

    PieceFactory* pieceFactory = new StandardPieceFactory();
    Piece* p;
    Piece* np;

    void combineVectors();
    bool isMovementAllowed(Direction direction);
    bool isRotationAllowed(Direction direction);
    void deleteCompleteRows();
    bool isVectorFilled(std::vector<int> v);
    void blankLevel(std::vector<std::vector<int>> &level, unsigned const int width, unsigned const int height);

    unsigned long long score;
    unsigned long long highscore;
    const int ROW_POINTS = 100;
    const int MULTIPLIER_FACTOR = 3;
};

#endif //SDLGAME_GAME_H
