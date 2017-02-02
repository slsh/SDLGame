//
// Created by johan eriksson on 31/01/2017.
//

#ifndef SDLGAME_GAME_H
#define SDLGAME_GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include "timer.h"
#include "Debugger.h"
#include "GraphicManager.h"

#include "pieces/factories/PieceFactory.h"
#include "pieces/factories/StandardPieceFactory.h"


class Game {
public:
    enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Game();
    ~Game() {}

    // simply set the running variable to true
    void init();

    //Prototypes
    void updateKey(SDL_KeyboardEvent *key);

    void combineVectors();
    void updateLogic();
    void movePiece(Direction direction);

    bool isMovementAllowed(Direction direction);
    void checkRows();
    void deleteRows(std::vector<int> lineNumbers);
    void updateWindow();
    void close();

    // a function to access the private running variable
    bool isRunning() { return gameRunning; }

    // TODO This is for testing
    PieceFactory* pieceFactory = new StandardPieceFactory();
    Piece* p;
    Piece* np;
    //Board* currentLevel;

    const int LEVELROW = 24;
    const int LEVELCOL = 12;
    GraphicManager* graphicManager;

private:

    bool gameRunning;
};

#endif //SDLGAME_GAME_H
