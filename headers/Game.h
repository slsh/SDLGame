//
// Created by johan eriksson on 31/01/2017.
//

#ifndef SDLGAME_GAME_H
#define SDLGAME_GAME_H

#include <SDL2/SDL.h>

class Game
{
public:
    Game() {}
    ~Game() {}

    // simply set the running variable to true
    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void init() { gameRunning = true; }
    void render(){}
    void update(){}
    void handleEvents(){}
    void clean(){}

    // a function to access the private running variable

    bool isRunning() { return gameRunning; }

private:
    SDL_Window *window;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* blitSurface = NULL;

    bool gameRunning;
};

#endif //SDLGAME_GAME_H
