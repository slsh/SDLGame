//
// Created by johan eriksson on 26/01/2017.
//

#include <SDL2/SDL.h>
#include <iostream>

#include "../headers/Game.h"
#include "../headers/timer.h"
#include "../headers/Debugger.h"
#include "../headers/pieces/TPiece.h"
#include "../headers/pieces/factories/PieceFactory.h"
#include "../headers/pieces/factories/StandardPieceFactory.h"

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const int SCREENH = 384;
const int SCREENW = 192;
const int LEVELROW = 24;
const int LEVELCOL = 12;

SDL_Window *window;
SDL_Surface* screenSurface = NULL;
SDL_Surface* blitSurface = NULL;
Debugger* dgb;

bool DEBUG = false;

// TODO This is for testing
PieceFactory* pieceFactory = new StandardPieceFactory();
Piece* p = pieceFactory->getRandomPiece();


std::vector<std::vector<int>> level(24, std::vector<int>(12,0));
std::vector<std::vector<int>> currentLevel(24, std::vector<int>(12,0));

//Proto
void updateKey(SDL_KeyboardEvent *key);
void close();
void updateWindow();
int main(int argc, char* argv[]);
void init();
void combineArrays();
void updateLogic();
void movePiece(int direction);
void updateBackground(std::vector< std::vector<int> > inputLevel);
void updatePieces(Piece* p);


void movePiece(Direction direction){
    switch (direction){
        case UP:
            //isMovementAllowed(UP);
            p->setX(p->getX() + -1);
            p->setY(p->getY() + 0);
            break;
        case DOWN:
            //isMovementAllowed(UP);
            p->setX(p->getX() + 1);
            p->setY(p->getY() + 0);
            break;
        case LEFT:
            //isMovementAllowed(UP);
            p->setX(p->getX() + 0);
            p->setY(p->getY() + -1);
            break;
        case RIGHT:
            //isMovementAllowed(UP);
            p->setX(p->getX() + 0);
            p->setY(p->getY() + 1);
            break;
        default:
            break;
    }
}

void updateLogic(){

}

void init(){
    //adjust size of vectors
    for (int i = 0; i < LEVELROW; ++i) {
        level.push_back(std::vector<int>());
        currentLevel.push_back(std::vector<int>());
    }
    for (int j = 0; j < LEVELCOL; ++j) {
        for (int i = 0; i < LEVELROW; ++i) {
            level[i].push_back(0);
            currentLevel[i].push_back(0);
        }
    }
}

void updateKey(SDL_KeyboardEvent *key){
    switch( key->keysym.sym ){
        case SDLK_UP:
            movePiece(UP);
            break;

        case SDLK_DOWN:
            movePiece(DOWN);
            break;

        case SDLK_LEFT:
            movePiece(LEFT);
            break;

        case SDLK_RIGHT:
            movePiece(RIGHT);
            break;

        case SDLK_ESCAPE:
            delete p;
            p = pieceFactory->getRandomPiece();
            break;

        case SDLK_SPACE:
            //p->rotateLeft();
            p->rotateRight();
            break;

        default:
            break;
    }
}

void updateWindow(){
    SDL_FillRect(blitSurface, NULL, 0);
    SDL_FillRect(screenSurface, NULL, 0);
    //Variables are globals, TODO Remember to fix this.
    updatePieces(p);
    updateBackground(currentLevel);

    //Apply the image
    SDL_UpdateWindowSurface( window );
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( screenSurface );
    screenSurface = NULL;

    SDL_FreeSurface( blitSurface );
    blitSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    SDL_Quit();
}


void screenSetup(){
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

}

//Drawing of bitmaps
void DrawBitmap(char *filename, int x, int y){
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.h = 16;
    dstrect.w = 16;

    //Load splash image
    blitSurface = SDL_LoadBMP( filename );
    SDL_BlitSurface( blitSurface, NULL, screenSurface, &dstrect);
}


//match color to drawbitmap
void updatePieces(Piece* p){ //int board[4][4]){
    int posX = p->getX();
    int posY = p->getY();
    std::vector<std::vector<int>> vec = p->getThisRotation();
    for (int i = 0; i < p->getThisRotation().size(); i++){ // Y
        for (int j = 0; j < vec[i].size(); j++){ // X
            switch (vec[i][j]){
                case 1:
                    DrawBitmap("../images/red.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 2:
                    DrawBitmap("../images/orange.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 3:
                    DrawBitmap("../images/yellow.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 4:
                    DrawBitmap("../images/green.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 5:
                    DrawBitmap("../images/bblue.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 6:
                    DrawBitmap("../images/dblue.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 7:
                    DrawBitmap("../images/magneta.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                default:
                    break;
            }
        }
    }
}

//Match right bitmap to drawbitmap
void updateBackground(std::vector< std::vector<int> > inputLevel){
//void updateBackground(int inputLevel[LEVELROW][LEVELCOL]){
    for (size_t i = 0; i < inputLevel.size(); i++){ // Y
        for (size_t j = 0; j < inputLevel[0].size(); j++){ // X
            switch (inputLevel[i][j])
            {
                case 0:
                    DrawBitmap("../images/white.bmp", j * 16, i * 16);
                    break;
                case 1:
                    DrawBitmap("../images/red.bmp", j * 16, i * 16);
                    break;
                case 2:
                    DrawBitmap("../images/orange.bmp", j * 16, i * 16);
                    break;
                case 3:
                    DrawBitmap("../images/yellow.bmp", j * 16, i * 16);
                    break;
                case 4:
                    DrawBitmap("../images/green.bmp", j * 16, i * 16);
                    break;
                case 5:
                    DrawBitmap("../images/bblue.bmp", j * 16, i * 16);
                    break;
                case 6:
                    DrawBitmap("../images/dblue.bmp", j * 16, i * 16);
                    break;
                case 7:
                    DrawBitmap("../images/magneta.bmp", j * 16, i * 16);
                    break;
                case 9:
                    DrawBitmap("../images/gray.bmp", j * 16, i * 16);
                    break;
                default:
                    break;
            }
        }
    }

}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        DEBUG = true;
    }
    //Main loop flag
    dgb = new Debugger(true);
    bool quit = false;
    Timer tmr;



    //Create the Window
    screenSetup();
    //Current time start time
    Uint32 startTime = 0;
    Uint32 resetTime = 0;


    //Event handler
    SDL_Event e;
    //While application is running
    while(!quit) {
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0) {
            //User requests quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }else if(e.type == SDL_KEYDOWN){
                SDL_FillRect(screenSurface, NULL, 0);
                updateKey(&e.key);
            }
        }

        startTime = SDL_GetTicks();
        //Time for automatic "falling"
        if ((startTime - resetTime) > 500){
            resetTime = SDL_GetTicks();
            movePiece(DOWN);
        }
        updateLogic();
        updateWindow();
    }


    //Free and close
    close();
    return 0;
}
