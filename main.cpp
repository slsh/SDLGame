//
// Created by johan eriksson on 26/01/2017.
//

#include <SDL2/SDL.h>
#include <stdio.h>

#include "headers/pieces.h"
#include "headers/timer.h"

const int SCREENH = 384;
const int SCREENW = 192;
const int LEVELROW = 24;
const int LEVELCOL = 12;

int currentLevel[LEVELROW][LEVELCOL];
int level[LEVELROW][LEVELCOL];



void updateKey(SDL_KeyboardEvent *key);
void updateLogic();
void updateWindow();
void close();
void loadMedia();
int main(int argc, char* argv[]);


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
void drawBackText(LPCSTR text, int y, int x);
void updateText();
void updateWindow(int inputLevel[LEVELROW][LEVELCOL]);
void updateBackground(int inputLevel[LEVELROW][LEVELCOL]);
void updatePieces(int posX, int posY, int board[4][4]);
void gameDown();
void updateLogic();

Pieces* p;
bool gameOver;
int score, lines = 0;
double timerPoint;

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
        Sleep(50);
        updateWindow(toDelete);
        Sleep(50);
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
                Sleep(20);
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

//Inputhandling
//Sleeps used for feeling of "control"
void updateInput(){
    //Quit
    if (GetAsyncKeyState(VK_ESCAPE)){
        OutputDebugString("VK_ESCAPE");
        PostQuitMessage(0);
    }
    //Rotate
    if (GetAsyncKeyState(VK_UP)){
        OutputDebugString("VK_UP");
        p->direction = ROTATE;
        tryRotatePiece();
        Sleep(50);
    }
    //Rotate
    if (GetAsyncKeyState(VK_SPACE)){
        OutputDebugString("VK_SPACE");
        p->direction = ROTATE;
        tryRotatePiece();
        Sleep(50);
    }

    //Fast Fall
    if (GetAsyncKeyState(VK_DOWN)){
        OutputDebugString("VK_DOWN");
        p->direction = DOWN;
        movePiece();
    }
    //Move left
    if (GetAsyncKeyState(VK_LEFT)){
        OutputDebugString("VK_LEFT");
        p->direction = LEFT;
        movePiece();
        Sleep(20);
    }
    //Move right
    if (GetAsyncKeyState(VK_RIGHT)){
        OutputDebugString("VK_RIGHT");
        p->direction = RIGHT;
        movePiece();
        Sleep(20);
    }

    if (gameOver){
        //Restart
        if (GetAsyncKeyState(VK_RETURN)){
            OutputDebugString("ENTER");
            initGame();
        }
    }

}
//Drawing of bitmaps
void DrawBitmap(char *filename, int x, int y){
    HBITMAP image = (HBITMAP)LoadImage(0, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    BITMAP bm;
    GetObject(image, sizeof(BITMAP), &bm);

    HDC hdcImage = CreateCompatibleDC(displayDevice);
    SelectObject(hdcImage, image);

    BitBlt(device, x, y, bm.bmWidth, bm.bmHeight, hdcImage, 0, 0, SRCCOPY);

    DeleteDC(hdcImage);
    DeleteObject((HBITMAP)image);
}

//Draw text
void drawBackText(LPCSTR text, int y, int x){
    HFONT       font;
    LOGFONT LogFont;
    LogFont.lfWeight = 12;
    font = CreateFontIndirect(&LogFont);
    if (!gameOver){
        SetBkMode(device, TRANSPARENT);
    }
    TextOut(device, y, x, (LPCSTR)text, 14);

    DeleteObject(font);
}

//Text for updates
void updateText(){
    TCHAR buffer[30] = "";
    TCHAR intbuffer[10] = "";
    int test = 99999;
    drawBackText("score: ", 0, 0);
    drawBackText("lines", 100, 0);

    buffer[0] = '\0';
    wsprintf(buffer, TEXT("%d"), score);
    drawBackText(buffer, 40, 0);

    intbuffer[0] = '\0';
    wsprintf(intbuffer, TEXT("%d"), lines);
    drawBackText(intbuffer, 140, 0);
}

//Draw at device and then copy to displayDevice to remove flickering
void updateWindow(int inputLevel[LEVELROW][LEVELCOL]){
    displayDevice = GetDC(window);
    HBITMAP hbMem;
    device = CreateCompatibleDC(displayDevice);
    hbMem = CreateCompatibleBitmap(displayDevice, 192, 384);

    hOld = SelectObject(device, hbMem);

    updateBackground(inputLevel);
    updatePieces(p->posX, p->posY, p->thisPiece);

    //Game over print
    if (gameOver){
        drawBackText("game over", SCREENW / 3, SCREENH / 2);
    }
    updateText();
    BitBlt(displayDevice, 0, 0, 192, 384, device, 0, 0, SRCCOPY);

    DeleteObject(hbMem);
    DeleteDC(device);

    ReleaseDC(window, device);
    ReleaseDC(window, displayDevice);
}

//Match right bitmap to drawbitmap
void updateBackground(int inputLevel[LEVELROW][LEVELCOL]){
    for (size_t i = 0; i < LEVELROW; i++){ // Y
        for (size_t j = 0; j < LEVELCOL; j++){ // X
            switch (inputLevel[i][j])
            {
                case 0:
                    DrawBitmap("white.bmp", j * 16, i * 16);
                    break;
                case 1:
                    DrawBitmap("red.bmp", j * 16, i * 16);
                    break;
                case 2:
                    DrawBitmap("orange.bmp", j * 16, i * 16);
                    break;
                case 3:
                    DrawBitmap("yellow.bmp", j * 16, i * 16);
                    break;
                case 4:
                    DrawBitmap("green.bmp", j * 16, i * 16);
                    break;
                case 5:
                    DrawBitmap("bblue.bmp", j * 16, i * 16);
                    break;
                case 6:
                    DrawBitmap("dblue.bmp", j * 16, i * 16);
                    break;
                case 7:
                    DrawBitmap("magneta.bmp", j * 16, i * 16);
                    break;
                case 9:
                    DrawBitmap("gray.bmp", j * 16, i * 16);
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
                    DrawBitmap("red.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 2:
                    DrawBitmap("orange.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 3:
                    DrawBitmap("yellow.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 4:
                    DrawBitmap("green.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 5:
                    DrawBitmap("bblue.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 6:
                    DrawBitmap("dblue.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                case 7:
                    DrawBitmap("magneta.bmp", (posY + j) * 16, (posX + i) * 16);
                    break;
                default:
                    break;
            }
        }
    }
}


void gameDown(){
    ReleaseDC(window, device);
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

/*
 * Functions to integrate to here
 */

SDL_Window *window;
SDL_Surface* screenSurface = NULL;
SDL_Surface* blitSurface = NULL;

void updateKey(SDL_KeyboardEvent *key){
    switch( key->keysym.sym ){
        case SDLK_UP:
            printf( "UpKey pressed\n" );
            break;

        case SDLK_DOWN:
            printf( "DownKey pressed\n" );
            break;

        default:
            break;
    }
}


void updateWindow(){
    //Apply the image
    SDL_BlitSurface( blitSurface, NULL, screenSurface, NULL );

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

void loadMedia() {
    //Load splash image
    blitSurface = SDL_LoadBMP( "hello_world.bmp" );
    if( blitSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
    }
}

int main(int argc, char* argv[]) {


    bool gameOn = true;
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

    loadMedia();

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

        //updateLogic();

        updateWindow();

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