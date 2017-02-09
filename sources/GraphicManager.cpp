//
// Created by johan eriksson on 02/02/2017.
//

#include "../headers/GraphicManager.h"


GraphicManager::GraphicManager(){
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            SCREENW,                               // width, in pixels
            SCREENH,                               // height, in pixels
            SDL_WINDOW_OPENGL                 // flags - see below
    );

    screenSurface = SDL_GetWindowSurface( window );

    // Check that the window was successfully created
    if (window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    }

    largeFont = TTF_OpenFont(fontFile.c_str(), 102);
    mediumFont = TTF_OpenFont(fontFile.c_str(), 72);
    smallFont = TTF_OpenFont(fontFile.c_str(), 48);
};

GraphicManager::~GraphicManager() {
    //Deallocate surface
    SDL_FreeSurface( screenSurface );
    screenSurface = NULL;

    SDL_FreeSurface( blitSurface );
    blitSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    SDL_Quit();

    TTF_CloseFont(largeFont);
    TTF_CloseFont(mediumFont);
    TTF_CloseFont(smallFont);

    TTF_Quit();
}

void GraphicManager::init(Game *newGame){
    game = newGame;
}



//Drawing of bitmaps
void GraphicManager::drawBitmap(char *filename, int x, int y, int width, int height){
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    //dstrect.h = height;
    //dstrect.w = width;

    //Load splash image
    blitSurface = SDL_LoadBMP( filename );
    SDL_BlitSurface( blitSurface, NULL, screenSurface, &dstrect);
}

void GraphicManager::drawBackground(int color, int x, int y, int width, int height){
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = width;
    dstrect.h = height;

    //Load splash image
    SDL_FillRect(screenSurface, &dstrect, color);
}

void GraphicManager::drawText(std::string str, FontSize size, int x, int y){
    SDL_Color clrFg = {255,255,255,0};
    TTF_Font *fontToUse = NULL;
    switch (size) {
        case LARGE:
            fontToUse = largeFont;
            break;
        case MEDIUM:
            fontToUse = mediumFont;
            break;
        case SMALL:
        default:
            fontToUse = smallFont;
    }

    SDL_Surface *sText = TTF_RenderText_Solid(fontToUse, str.c_str() , clrFg);
    SDL_Rect rcDest = {x,y,0,0};
    SDL_BlitSurface(sText, NULL, screenSurface,&rcDest);
    SDL_FreeSurface(sText);
}


//match color to drawbitmap
void GraphicManager::updatePieces(Piece* p){ //int board[4][4]){
    int posX = p->getX();
    int posY = p->getY();
    std::vector<std::vector<int>> vec = p->getThisRotation();
    for (int i = 0; i < p->getThisRotation().size(); i++){ // Y
        for (int j = 0; j < vec[i].size(); j++){ // X
            switch (vec[i][j]){
                case 1:
                    drawBitmap((char *) "../images/red.bmp", (posY + j) * 16, (posX + i) * 16, 16, 16);
                    break;
                case 2:
                    drawBitmap((char *) "../images/orange.bmp", (posY + j) * 16, (posX + i) * 16, 16, 16);
                    break;
                case 3:
                    drawBitmap((char *) "../images/yellow.bmp", (posY + j) * 16, (posX + i) * 16, 16, 16);
                    break;
                case 4:
                    drawBitmap((char *) "../images/green.bmp", (posY + j) * 16, (posX + i) * 16, 16, 16);
                    break;
                case 5:
                    drawBitmap((char *) "../images/bblue.bmp", (posY + j) * 16, (posX + i) * 16, 16, 16);
                    break;
                case 6:
                    drawBitmap((char *) "../images/dblue.bmp", (posY + j) * 16, (posX + i) * 16, 16, 16);
                    break;
                case 7:
                    drawBitmap((char *) "../images/magneta.bmp", (posY + j) * 16, (posX + i) * 16, 16, 16);
                    break;
                default:
                    break;
            }
        }
    }
}

//Match right bitmap to drawbitmap
void GraphicManager::updateBackground(std::vector< std::vector<int> > inputLevel){
    for (int i = 0; i < inputLevel.size(); i++){ // Y
        for (int j = 0; j < inputLevel[0].size(); j++){ // X
            switch (inputLevel[i][j])
            {
                case 0:
                    drawBitmap((char *) "../images/white.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 1:
                    drawBitmap((char *) "../images/red.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 2:
                    drawBitmap((char *) "../images/orange.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 3:
                    drawBitmap((char *) "../images/yellow.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 4:
                    drawBitmap((char *) "../images/green.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 5:
                    drawBitmap((char *) "../images/bblue.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 6:
                    drawBitmap((char *) "../images/dblue.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 7:
                    drawBitmap((char *) "../images/magneta.bmp", j * 16, i * 16, 16, 16);
                    break;
                case 9:
                    drawBitmap((char *) "../images/gray.bmp", j * 16, i * 16, 16, 16);
                    break;
                default:
                    break;
            }
        }
    }
}

void GraphicManager::close()
{

}

void GraphicManager::paintBackground(){
    //Repaint the two backgrounds
    drawBackground(BLACK, 0, 0, SCREENW / 2, SCREENH);
    drawBackground(BLACK, 194, 0, SCREENW / 2, SCREENH);
    drawBackground(GREY_LIGHT, 192, 0, 2, SCREENH);
}

void GraphicManager::updateWindow(){
    paintBackground();

    drawText("Next Piece", SMALL, 240, 0);
    drawText("Score:", SMALL, 240, 120);
    drawText(std::to_string(game->getScore()), SMALL, 240, 140);

    drawText("HighScore:", SMALL, 240, 160);
    drawText(std::to_string(game->getHighScore()), SMALL, 240, 180);


    updatePieces(game->getCurrentPiece());            //Update the falling piece
    updatePieces(game->getNextPiece());               //Update the next piece
    updateBackground(game->currentLevel); //Update the LEVEL background

    if(game->isGameOver()){drawText("Game Over!", MEDIUM, (384 / 6) , 192);}
    if(game->isPaused()){drawText("PAUSED", MEDIUM, (384 / 6) , 192);}

    //Apply the image
    SDL_UpdateWindowSurface(window);
}