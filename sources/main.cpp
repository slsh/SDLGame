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
void combineVectors();
void updateLogic();
void movePiece(int direction);
void updateBackground(std::vector< std::vector<int> > inputLevel);
void updatePieces(Piece* p);
bool isMovementAllowed(Direction direction);
void checkRows();
void deleteRows(int filled[4]);

//Delete rows
void deleteRows(std::vector<int> lineNumbers){
    //Locate the rows to be deleted, move them to array toDelete
    std::vector< std::vector<int> > toDelete(24, std::vector<int>(12,0));
    std::copy(currentLevel.begin(), currentLevel.end(), toDelete.begin()); //Copy current state
    /*
    //std::copy(&currentLevel[0][0], &currentLevel[0][0] + LEVELCOL * LEVELROW, &toDelete[0][0]);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            toDelete[i][j] = currentLevel[i][j];
        }
    }
    */
    for (int i = 0; i < 4; i++){
        if (lineNumbers[i] > 0){
            for (int j = 0; j < LEVELCOL; j++){
                toDelete[lineNumbers[i]][j] = 9;
            }
        }
    }


    //Actual removal in the new array
    for (int i = LEVELROW -1; i > 0; i--){
        if (toDelete[i][0] == 9){
            for (int j = i; j > 0; j--){
                for (int k = 0; k < LEVELCOL; k++){
                    toDelete[j][k] = toDelete[j - 1][k];
                }
            }
            //Move back one step on delete
            i++;
        }
    }
    std::copy(toDelete.begin(), toDelete.end(), currentLevel.begin()); //Copy current state
}

//Check for complete rows
void checkRows(){
    std::vector<int> lineNumbers(5, -1);
    bool completeRow;
    bool aRowIsFilled = false;
    int j, filledRow = 0;
    for (int i = 0; i < LEVELROW; i++){
        completeRow = true;
        j = 0;
        while (completeRow){
            if (currentLevel[i][j] == 0){
                completeRow = false;
            } else{
                j++;
            }
            if (j == LEVELCOL){
                break;
            }
        }
        //Saved fill rows, max 4 as "floating rows" are allowed
        if (completeRow){
            lineNumbers[filledRow] = i;
            filledRow++;
            aRowIsFilled = true;
        }
    }
    if (aRowIsFilled){
        deleteRows(lineNumbers);
    }
}

void movePiece(Direction direction){
    switch (direction){
        case UP:
            if(isMovementAllowed(UP)) {
                p->setX(p->getX() + -1);
            }
            break;
        case DOWN:
            if(isMovementAllowed(DOWN)) {
                p->setX(p->getX() + 1);
            }else{
                combineVectors();
                checkRows();
                delete p;
                p = pieceFactory->getRandomPiece();
            }
            break;
        case LEFT:
            if(isMovementAllowed(LEFT)) {
                p->setY(p->getY() + -1);
            }
            break;
        case RIGHT:
            if(isMovementAllowed(RIGHT)) {
                p->setY(p->getY() + 1);
            }
            break;
        default:
            break;
    }
}

void updateLogic(){

}

void combineVectors(){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (p->getThisRotation()[i][j] > 0){
                currentLevel[p->getX() + i][p->getY() + j] = p->getThisRotation()[i][j];
            } else{
            }
        }
    }
}

bool isMovementAllowed(Direction direction){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (p->getThisRotation()[i][j] > 0){
                switch (direction)
                {
                    case UP:
                        break;
                    case DOWN:
                        //Check for bottom
                        if (i + 1 + p->getX() > 23){
                            return false;
                        }
                        //Check for other pieces
                        if (currentLevel[i + 1 + p->getX()][j + p->getY()] > 0){
                            return false;
                        }
                        break;
                    case LEFT:
                        //Check for other pieces
                        if (currentLevel[i + p->getX()][j - 1 + p->getY()] > 0){
                            return false;
                        }
                        //Check MAX
                        if (j + p->getY() - 1 < 0){
                            return false;
                        }
                        break;
                    case RIGHT:
                        //Check for other pieces
                        if (currentLevel[i + p->getX()][j + 1 + p->getY()] > 0){
                            return false;
                        }
                        //Check MAX
                        if (j + p->getY() + 1 > 11) {
                            return false;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return true;
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
