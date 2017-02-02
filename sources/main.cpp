//
// Created by johan eriksson on 26/01/2017.
//

#include "../headers/Game.h"

//Debugger
Debugger* dgb;
bool DEBUG = false;

Game* g_game = 0;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        DEBUG = true;
    }
    //Main loop flag
    dgb = new Debugger(true);
    bool quit = false;

    g_game = new Game();
    //Current time start time
    Uint32 startTime = 0;
    Uint32 resetTime = 0;
    //Event handler
    SDL_Event e;

    g_game->init();
    while(g_game->isRunning()) {
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                g_game->close();
            } else if (e.type == SDL_KEYDOWN) {
                //SDL_FillRect(screenSurface, NULL, 0);
                g_game-> updateKey(&e.key);

            }
        }
        startTime = SDL_GetTicks();

        if ((startTime - resetTime) > 500){
            resetTime = SDL_GetTicks();
            g_game->movePiece(g_game->DOWN);
        }
        //g_game->updateLogic();
        g_game->updateWindow();
    }
    g_game->close();
    return 0; }
