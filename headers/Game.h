//
// Created by johan eriksson on 31/01/2017.
//

#ifndef SDLGAME_GAME_H
#define SDLGAME_GAME_H

#include <SDL2/SDL.h>

#include <iostream>
#include "timer.h"
#include "Debugger.h"
#include "pieces/TPiece.h"
#include "pieces/factories/PieceFactory.h"
#include "pieces/factories/StandardPieceFactory.h"
#include "Colors.h"

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
    void close();

    //Prototypes
    void updateKey(SDL_KeyboardEvent *key);
    void screenSetup();
    void updateWindow();
    void combineVectors();
    void updateLogic();
    void movePiece(Direction direction);
    void updateBackground(std::vector< std::vector<int> > inputLevel);
    void updatePieces(Piece* p);
    bool isMovementAllowed(Direction direction);
    void checkRows();
    void deleteRows(std::vector<int> lineNumbers);
    void DrawBitmap(char *filename, int x, int y, int width, int height);
    void DrawBackground(int color, int x, int y, int width, int height);

    // a function to access the private running variable
    bool isRunning() { return gameRunning; }

    // TODO This is for testing
    PieceFactory* pieceFactory = new StandardPieceFactory();
    Piece* p;
    Piece* np;// = pieceFactory->getRandomPiece();
    //std::vector<std::vector<int>> level(24, std::vector<int>(12,0));
    //std::vector<std::vector<int>> currentLevel(24, std::vector<int>(12,0));

private:
    SDL_Window *window;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* blitSurface = NULL;
    const int SCREENH = 384;
    const int SCREENW = 192 + 192;
    const int LEVELROW = 24;
    const int LEVELCOL = 12;
    //std::vector<std::vector<int>> currentLevel;//(24, std::vector<int>(12,0));
    //std::vector<std::vector<int>> currentLevel;//(24, std::vector<int>(12,0));
    bool gameRunning;
};

#endif //SDLGAME_GAME_H
