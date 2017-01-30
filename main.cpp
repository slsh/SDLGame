//
// Created by johan eriksson on 26/01/2017.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <time.h>

#include "headers/pieces.h"
#include "headers/timer.h"
#include "headers/Debugger.h"

const int SCREENH = 384;
const int SCREENW = 192;
const int LEVELROW = 24;
const int LEVELCOL = 12;

//Global
std::vector< std::vector<int> > currentLevel;
std::vector< std::vector<int> > level;
bool DEBUG = false;
SDL_Window *window;
SDL_Surface* screenSurface = NULL;
SDL_Surface* blitSurface = NULL;
Debugger* dgb;

Pieces* currentPiece;
Pieces* nextPiece;

bool gameOver;
int score, lines = 0;
double timerPoint;

//Proto
void updateKey(SDL_KeyboardEvent *key);
void updateLogic();
void close();
void lostGame();
Pieces newPiece();
void combineArrays();
void tryRotatePiece();
void updateScore(int scoreMultiplier);
void deleteRows(int filled[4]);
void checkRows();
void movePiece();
bool isMovementAllowed(std::vector< std::vector<int> >piece); //int piece[4][4]);
void initGame();
void updateInput();
void DrawBitmap(char *filename, int x, int y);
void updateWindow(std::vector< std::vector<int> > inputLevel); //int inputLevel[LEVELROW][LEVELCOL]);
void updateBackground(std::vector< std::vector<int> > inputLevel); //int inputLevel[LEVELROW][LEVELCOL]);
void updatePieces(int posX, int posY, std::vector< std::vector<int> > board); //int board[4][4]);
void levelCreator();
int main(int argc, char* argv[]);


void updateKey(SDL_KeyboardEvent *key){
    switch( key->keysym.sym ){
        case SDLK_UP:
            dgb->outputDebugString("VK_UP");
            currentPiece->direction = ROTATE;
            tryRotatePiece();
            SDL_Delay(50);
            break;

        case SDLK_DOWN:
            dgb->outputDebugString("VK_DOWN");
            currentPiece->direction = DOWN;
            movePiece();
            break;
        case SDLK_SPACE:
            dgb->outputDebugString("VK_SPACE");
            currentPiece->direction = ROTATE;
            tryRotatePiece();
            SDL_Delay(50);
            break;
        case SDLK_LEFT:
            dgb->outputDebugString("VK_LEFT");
            currentPiece->direction = LEFT;
            movePiece();
            SDL_Delay(20);
            break;
        case SDLK_RIGHT:
            dgb->outputDebugString("VK_RIGHT");
            currentPiece->direction = RIGHT;
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

void updateWindow(std::vector< std::vector<int> > inputLevel){
//void updateWindow(int inputLevel[LEVELROW][LEVELCOL]){
    updateBackground(inputLevel);
    updatePieces(currentPiece->posX, currentPiece->posY, currentPiece->thisPiece);

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


void lostGame(){
    gameOver = true;
}

Pieces newPiece(){
    if (!gameOver){
        if (currentPiece != NULL){
            delete currentPiece;
        }
        currentPiece = new Pieces();
        currentPiece->direction = DOWN;
        if (!isMovementAllowed(currentPiece->thisPiece)){
            lostGame();
        }
    }

}

//Merge arrays
void combineArrays(){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (currentPiece->thisPiece[i][j] > 0){
                currentLevel[currentPiece->posX + i][currentPiece->posY + j] = currentPiece->thisPiece[i][j];
            } else{
            }
        }
    }
}

//Check if rotation is possible
void tryRotatePiece(){
    if (isMovementAllowed(currentPiece->nextPiece)){
        Pieces::rotatePiece(currentPiece);
    }
}

void updateScore(int scoreMultiplier){
    score += (100 * scoreMultiplier);
}

//Delete rows
void deleteRows(int filled[4]){
    //Locate the rows to be deleted, move them to array toDelete
    int scoreMultiplier = 1;
    std::vector< std::vector<int> > toDelete; //int toDelete[LEVELROW][LEVELCOL];
    //std::copy(&currentLevel[0][0], &currentLevel[0][0] + LEVELCOL * LEVELROW, &toDelete[0][0]);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            toDelete[i][j] = currentLevel[i][j];
        }
    }

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
    if (isMovementAllowed(currentPiece->thisPiece)){
        switch (currentPiece->direction)
        {
            case UP:
                currentPiece->posX += -1;
                break;
            case DOWN:
                currentPiece->posX += 1;
                SDL_Delay(20);
                break;
            case LEFT:
                currentPiece->posY += -1;
                break;
            case RIGHT:
                currentPiece->posY += 1;
                break;
            default:
                break;
        }
    } else{
        if (currentPiece->direction == DOWN){
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
//bool isMovementAllowed(int piece[4][4]){
bool isMovementAllowed(std::vector< std::vector<int> > piece){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (piece[i][j] > 0){
                switch (currentPiece->direction)
                {
                    case UP:
                        break;
                    case DOWN:
                        //Check for other pieces
                        if (currentLevel[i + 1 + currentPiece->posX][j + currentPiece->posY] > 0){
                            return false;
                        }
                        //Check for bottom
                        if (i + 1 + currentPiece->posX > 23){
                            return false;
                        }
                        break;
                    case LEFT:
                        //Check for other pieces
                        if (currentLevel[i + currentPiece->posX][j - 1 + currentPiece->posY] > 0){
                            return false;
                        }
                        //Check MAX
                        if (j + currentPiece->posY - 1 < 0){
                            return false;
                        }
                        break;
                    case RIGHT:
                        //Check for other pieces
                        if (currentLevel[i + currentPiece->posX][j + 1 + currentPiece->posY] > 0){
                            return false;
                        }
                        //Check MAX
                        if (j + currentPiece->posY + 1 > 11) {
                            return false;
                        }
                        break;
                    case ROTATE:
                        //Check for other pieces and Limit
                        if ((currentLevel[i + currentPiece->posX][j + currentPiece->posY] > 0) ||
                            (j + currentPiece->posY - 1 < 0) ||
                            (j + currentPiece->posY + 1 > 11) ){
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

void levelCreator(){
    for (int i = 0; i < LEVELCOL; ++i) {
        currentLevel.push_back(std::vector<int>());
        level.push_back(std::vector<int>());
        for (int j = 0; j < LEVELROW; ++j) {
            currentLevel[i].push_back(0);
            level[i].push_back(0);
        }
    }

}

void initGame(){
    levelCreator();
    gameOver = false;
    std::copy(&level[0][0], &level[0][0] + LEVELCOL * LEVELROW, &currentLevel[0][0]);
    newPiece();
    score = 0;
    srand(time(NULL));
    Timer tmr;
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

//match color to drawbitmap
void updatePieces(int posX, int posY, std::vector< std::vector<int> > board){ //int board[4][4]){
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

int main(int argc, char* argv[]) {
    if (argc > 1) {
        DEBUG = true;
    }

    dgb = new Debugger(true);

    //Create the Window
    screenSetup();

    //Main loop flag
    bool quit = false;
    Timer tmr;

    //Iniate the first game
    initGame();

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
                //Pieces::testPiece();
            }
        }


        //updateLogic();
        //updateWindow(currentLevel);

        /*Time for automatic "falling"
        if (tmr.elapsed() > timerPoint){
            currentPiece->direction = DOWN;
            movePiece();
            tmr.reset();
        }
        */

    }


    //Free and close
    close();
    return 0;
}