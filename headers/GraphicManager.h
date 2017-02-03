//
// Created by johan eriksson on 02/02/2017.
//

#ifndef SDLGAME_GRAPHICMANAGER_H
#define SDLGAME_GRAPHICMANAGER_H
#include <SDL2/SDL.h>
#include "Colors.h"
#include "pieces/factories/PieceFactory.h"

#if defined(__APPLE__)
#include <SDL_ttf.h>
#elif defined(__UNIX__)
#include <SDL2/SDL_ttf.h>
#endif



class GraphicManager {
public:
    GraphicManager();
    ~GraphicManager() {close(); TTF_Quit();}
    void close();
    void updateWindow(Piece* p, Piece* np, std::vector<std::vector <int>> currentLevel);

    void init();

    void updateBackground(std::vector< std::vector<int> > inputLevel);
    void updatePieces(Piece* p);
    void paintBackground();

    void drawBitmap(char *filename, int x, int y, int width, int height);
    void drawBackground(int color, int x, int y, int width, int height);
    void drawText(std::string str, int color, int x, int y, int width, int height);

private:
    const int SCREENH = 384;
    const int SCREENW = 192 + 192 + 2;

    SDL_Window* window;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* blitSurface = NULL;
    SDL_Surface* textSurface = NULL;
    SDL_Surface* color_white = NULL;
    SDL_Surface* color_red = NULL;
    SDL_Surface* color_orange = NULL;
    SDL_Surface* color_yellow = NULL;
    SDL_Surface* color_green = NULL;
    SDL_Surface* color_bblue = NULL;
    SDL_Surface* color_dblue = NULL;
    SDL_Surface* color_magneta = NULL;
    SDL_Surface* color_grey = NULL;
};


#endif //SDLGAME_GRAPHICMANAGER_H
