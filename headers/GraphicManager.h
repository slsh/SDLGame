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
#elif defined(__linux__)
#include <SDL2/SDL_ttf.h>
#endif



class GraphicManager {
public:
    GraphicManager();
    ~GraphicManager();

    enum FontSize {
        LARGE,
        MEDIUM,
        SMALL
    };

    void close();
    void updateWindow(Piece* p, Piece* np, std::vector<std::vector <int>> currentLevel);

    void init();

    void updateBackground(std::vector< std::vector<int> > inputLevel);
    void updatePieces(Piece* p);
    void paintBackground();

    void drawBitmap(char *filename, int x, int y, int width, int height);
    void drawBackground(int color, int x, int y, int width, int height);
    void drawText(std::string str, FontSize size, int x, int y);

private:
    const int SCREENH = 384;
    const int SCREENW = 192 + 192 + 2;
    const std::string fontFile = "../data/Game-Over.ttf";

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

    TTF_Font *largeFont = NULL;
    TTF_Font *mediumFont = NULL;
    TTF_Font *smallFont = NULL;
};


#endif //SDLGAME_GRAPHICMANAGER_H
