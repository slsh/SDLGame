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

    //Prototypes
    void init();
    void updateKey(SDL_KeyboardEvent *key);
    void movePiece(Direction direction);
    void updateWindow();
    void close();
    // a function to access the private running variable
    bool isRunning() { return gameRunning; }


private:
    const int LEVELROW = 24;
    const int LEVELCOL = 12;
    bool gameRunning;
    GraphicManager* graphicManager;

    PieceFactory* pieceFactory = new StandardPieceFactory();
    Piece* p;
    Piece* np;
    //Board* currentLevel;

    void combineVectors();
    bool isMovementAllowed(Direction direction);
    void checkRows();
    void deleteRows(std::vector<int> lineNumbers);

};

#endif //SDLGAME_GAME_H
