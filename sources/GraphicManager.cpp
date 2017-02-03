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
};

void GraphicManager::init(){

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

void GraphicManager::drawText(std::string str, int color, int x, int y, int width, int height){

    TTF_Font *fntCourier = TTF_OpenFont( "../images/Game-Over.ttf", 48 );

    SDL_Color clrFg = {255,255,255,0};  // Blue ("Fg" is foreground)

    SDL_Surface *sText = TTF_RenderText_Solid( fntCourier, str.c_str() , clrFg );

    SDL_Rect rcDest = {x,y,0,0};

    SDL_BlitSurface( sText,NULL, screenSurface,&rcDest );

    SDL_FreeSurface( sText );
    TTF_CloseFont( fntCourier );
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
    //Deallocate surface
    SDL_FreeSurface( screenSurface );
    screenSurface = NULL;

    SDL_FreeSurface( blitSurface );
    blitSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //gameRunning = false;
    SDL_Quit();
}


void GraphicManager::updateWindow(Piece* p, Piece* np, std::vector<std::vector <int>> currentLevel){
    //Repaint the two backgrounds
    drawBackground(BLACK, 0, 0, SCREENW / 2, SCREENH);
    drawBackground(BLACK, 194, 0, SCREENW / 2, SCREENH);
    drawBackground(GREY_LIGHT, 192, 0, 2, SCREENH); //TODO change to white line
    drawText("NextPiece", GREY_LIGHT, 240, 100, 2, SCREENH);

    updatePieces(p);                //Update the falling piece
    updatePieces(np);               //Update the next piece
    updateBackground(currentLevel); //Update the LEVEL background

    //Apply the image
    SDL_UpdateWindowSurface( window );
}