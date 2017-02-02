//
// Created by johan eriksson on 02/02/2017.
//

#ifndef SDLGAME_GRAPHICMANAGER_H
#define SDLGAME_GRAPHICMANAGER_H
#include <SDL2/SDL.h>
#include "Colors.h"
#include "pieces/factories/PieceFactory.h"


class GraphicManager {
public:
    GraphicManager();
    ~GraphicManager() {close();}
    void close();
    void updateWindow(Piece* p, Piece* np, std::vector<std::vector <int>> currentLevel);

    void updateBackground(std::vector< std::vector<int> > inputLevel);
    void updatePieces(Piece* p);

    void drawBitmap(char *filename, int x, int y, int width, int height);
    void drawBackground(int color, int x, int y, int width, int height);
    void drawText(int color, int x, int y, int width, int height);

private:
    const int SCREENH = 384;
    const int SCREENW = 192 + 192 + 2;

    SDL_Window *window;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* blitSurface = NULL;


};


#endif //SDLGAME_GRAPHICMANAGER_H
