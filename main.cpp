//
// Created by johan eriksson on 26/01/2017.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "headers/pieces.h"
#include "headers/timer.h"
#include "headers/Debugger.h"

const int SCREENH = 384;
const int SCREENW = 192;
const int LEVELROW = 24;
const int LEVELCOL = 12;
bool DEBUG = false;

int currentLevel[LEVELROW][LEVELCOL];
int level[LEVELROW][LEVELCOL];


void updateKey(SDL_KeyboardEvent *key);
void updateLogic();
//void updateWindow();
void close();
void loadMedia();
int main(int argc, char* argv[]);

SDL_Window *window;
SDL_Surface* screenSurface = NULL;
SDL_Surface* blitSurface = NULL;

Debugger* dgb = new Debugger(true);

/*
 * Functions to integrate from here
 */

void lostGame();
void newPiece();
void combineArrays();
void tryRotatePiece();
void updateScore(int scoreMultiplier);
void deleteRows(int filled[4]);
void checkRows();
void movePiece();
bool isMovementAllowed(int piece[4][4]);
void initGame();
void updateInput();
void DrawBitmap(char *filename, int x, int y);
//void drawBackText(std::string text, int y, int x);
//void updateText();
void updateWindow(int inputLevel[LEVELROW][LEVELCOL]);
void updateBackground(int inputLevel[LEVELROW][LEVELCOL]);
void updatePieces(int posX, int posY, int board[4][4]);
void gameDown();

Pieces* p;
bool gameOver;
int score, lines = 0;
double timerPoint;


void updateKey(SDL_KeyboardEvent *key){
    switch( key->keysym.sym ){
        case SDLK_UP:
            dgb->outputDebugString("VK_UP");
            p->direction = ROTATE;
            tryRotatePiece();
            SDL_Delay(50);
            break;

        case SDLK_DOWN:
            dgb->outputDebugString("VK_DOWN");
            p->direction = DOWN;
            movePiece();
            break;
        case SDLK_SPACE:
            dgb->outputDebugString("VK_SPACE");
            p->direction = ROTATE;
            tryRotatePiece();
            SDL_Delay(50);
            break;
        case SDLK_LEFT:
            dgb->outputDebugString("VK_LEFT");
            p->direction = LEFT;
            movePiece();
            SDL_Delay(20);
            break;
        case SDLK_RIGHT:
            dgb->outputDebugString("VK_RIGHT");
            p->direction = RIGHT;
            movePiece();
            SDL_Delay(20);
            break;
        case SDLK_KP_ENTER:
            //Restart
            dgb->outputDebugString("ENTER");
            if (gameOver){
                    initGame();
                }
            break;
        default:
            break;


    }
}


void updateWindow(int inputLevel[LEVELROW][LEVELCOL]){
    updateBackground(inputLevel);
    updatePieces(p->posX, p->posY, p->thisPiece);

    //Apply the image


    SDL_UpdateWindowSurface( window );
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

void loadMedia() {


    if( blitSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "../images/bblue.bmp", SDL_GetError() );
    }

}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        DEBUG = true;
    }


    dgb->outputDebugString("Heeej");

    Timer tmr;

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
        return 1;
    }

    //loadMedia();

    //Main loop flag
    bool quit = false;

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
                updateKey(&e.key);
            }
        }
        updateLogic();
        updateWindow(currentLevel);

        //Time for automatic "falling"
        if (tmr.elapsed() > timerPoint){
            p->direction = DOWN;
            movePiece();
            tmr.reset();
        }
    }

    //Free and close
    close();
    return 0;
}

void lostGame(){
    gameOver = true;
}

void newPiece(){
    if (!gameOver){
        if (p != NULL){
            destroyPiece(p);
        }
        p = createPiece();
        p->direction = DOWN;
        if (!isMovementAllowed(p->thisPiece)){
            lostGame();
        }
    }
}

//Merge arrays
void combineArrays(){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (p->thisPiece[i][j] > 0){
                currentLevel[p->posX + i][p->posY + j] = p->thisPiece[i][j];
            } else{
            }
        }
    }
}

//Check if rotation is possible
void tryRotatePiece(){
    if (isMovementAllowed(p->nextPiece)){
        rotatePiece(p);
    }
}

void updateScore(int scoreMultiplier){
    score += (100 * scoreMultiplier);
}


//Delete rows
void deleteRows(int filled[4]){
    //Locate the rows to be deleted, move them to array toDelete
    int scoreMultiplier = 1;
    int toDelete[LEVELROW][LEVELCOL];
    std::copy(&currentLevel[0][0], &currentLevel[0][0] + LEVELCOL * LEVELROW, &toDelete[0][0]);
    for (int i = 0; i < 4; i++){
        if (filled[i] > 0){
            for (int j = 0; j < LEVELCOL; j++){
                toDelete[filled[i]][j] = 9;
            }
        }
    }
    //Flash effect by freezing
    for (int i = 0; i < 5; i++){
        updateWindow(currentLevel);
        SDL_Delay(50);
        updateWindow(toDelete);
        SDL_Delay(50);
    }

    //Actual removal in the new array
    for (int i = LEVELROW; i > 0; i--){
        if (toDelete[i][0] == 9){
            for (int j = i; j > 0; j--){
                for (int k = 0; k < LEVELCOL; k++){
                    toDelete[j][k] = toDelete[j - 1][k];
                }
            }
            //Move back one step on delete
            i++;
            lines++;
            scoreMultiplier *= 4;
        }
    }
    //Update main array
    std::copy(&toDelete[0][0], &toDelete[0][0] + LEVELCOL * LEVELROW, &currentLevel[0][0]);
    updateScore(scoreMultiplier);
    updateWindow(currentLevel);
}

//Check for complete rows
void checkRows(){
    int filled[] = { -1, -1, -1, -1 };
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
            filled[filledRow] = i;
            filledRow++;
            aRowIsFilled = true;
        }
    }
    if (aRowIsFilled){
        deleteRows(filled);
    }
}

//Movement of pieces
void movePiece(){
    if (isMovementAllowed(p->thisPiece)){
        switch (p->direction)
        {
            case UP:
                p->posX += -1;
                break;
            case DOWN:
                p->posX += 1;
                SDL_Delay(20);
                break;
            case LEFT:
                p->posY += -1;
                break;
            case RIGHT:
                p->posY += 1;
                break;
            default:
                break;
        }
    } else{
        if (p->direction == DOWN){
            //Combine piece and board arrays
            combineArrays();
            //Check for complete rows
            checkRows();
            //New piece
            newPiece();
        }
    }

}

//Check if movement is possible depending on piece direction
bool isMovementAllowed(int piece[4][4]){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (piece[i][j] > 0){
                switch (p->direction)
                {
                    case UP:
                        break;
                    case DOWN:
                        //Check for other pieces
                        if (currentLevel[i + 1 + p->posX][j + p->posY] > 0){
                            return false;
                        }
                        //Check for bottom
                        if (i + 1 + p->posX > 23){
                            return false;
                        }
                        break;
                    case LEFT:
                        //Check for other pieces
                        if (currentLevel[i + p->posX][j - 1 + p->posY] > 0){
                            return false;
                        }
                        //Check MAX
                        if (j + p->posY - 1 < 0){
                            return false;
                        }
                        break;
                    case RIGHT:
                        //Check for other pieces
                        if (currentLevel[i + p->posX][j + 1 + p->posY] > 0){
                            return false;
                        }
                        //Check MAX
                        if (j + p->posY + 1 > 11) {
                            return false;
                        }
                        break;
                    case ROTATE:
                        //Check for other pieces and Limit
                        if ((currentLevel[i + p->posX][j + p->posY] > 0) ||
                            (j + p->posY - 1 < 0) ||
                            (j + p->posY + 1 > 11) ){
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


void initGame(){
    gameOver = false;
    std::copy(&level[0][0], &level[0][0] + LEVELCOL * LEVELROW, &currentLevel[0][0]);
    newPiece();
    score = 0;
}


////Everything up is checked////Everything up is checked////Everything up is checked////Everything up is checked////Everything up is checked



//Match right bitmap to drawbitmap
void updateBackground(int inputLevel[LEVELROW][LEVELCOL]){
    for (size_t i = 0; i < LEVELROW; i++){ // Y
        for (size_t j = 0; j < LEVELCOL; j++){ // X
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

//match color to drawbitmap
void updatePieces(int posX, int posY, int board[4][4]){
    for (int i = 0; i < 4; i++){ // Y
        for (int j = 0; j < 4; j++){ // X
            switch (board[i][j]){
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


// Basic tracker of automatic speed
void updateLogic(){
    if (score < 10000){
        timerPoint = 1;
    } else if (score < 20000){
        timerPoint = 0.8;
    } else if (score < 25000){
        timerPoint = 0.6;
    } else {
        timerPoint = 0.2;
    }
}