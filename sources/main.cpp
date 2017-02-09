//
// Created by johan eriksson on 26/01/2017.
//

#include "../headers/Game.h"
#include "../headers/GraphicManager.h"

//Debugger
Debugger* dgb;
bool DEBUG = false;

Game* game = 0;
GraphicManager* graphicManager = 0;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        DEBUG = true;
    }
    //Main loop flag
    dgb = new Debugger(true);
    bool quit = false;
    //Create window/gfx object
    game = new Game();
    graphicManager = new GraphicManager();

    graphicManager->init(game);

    //Current time start time
    Uint32 startTime = 0;
    Uint32 resetTime = 0;
    //Event handler
    SDL_Event e;
    game->init();
    while(game->isRunning()) {
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                game->close();
            } else if (e.type == SDL_KEYDOWN) {
                //SDL_FillRect(screenSurface, NULL, 0);
                game-> updateKey(&e.key);
            }
        }
        startTime = SDL_GetTicks();

        if (((startTime - resetTime) > 1000 / game->getSpeed()) & !game->isPaused()){
            resetTime = SDL_GetTicks();
            game->movePiece(game->DOWN);
        }
        //game->updateLogic();
        graphicManager->updateWindow();
    }
    delete game;
    return 0;
}
/*

graphicManager->close();
 */