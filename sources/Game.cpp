//
// Created by johan eriksson on 31/01/2017.
//

#include "../headers/Game.h"
#include "../headers/GraphicManager.h"

std::vector<std::vector<int>> currentLevel(24, std::vector<int>(12,0)); //TODO Move back to private

Game::Game() {
    //Create window/gfx object
    graphicManager = new GraphicManager();
    gameRunning = true;
}

void Game::init(){
    //Create initial two pieces
    p = pieceFactory->getRandomPiece();
    p->randomizeRotation();
    p->setY(0);
    p->setX(4);
    np = pieceFactory->getRandomPiece();
}


void Game::updateWindow(){
    graphicManager->updateWindow(p, np,currentLevel);
}

void Game::close(){
    graphicManager->close();
}

//Delete rows using 2 vectors for "flash effect"
void Game::deleteRows(std::vector<int> lineNumbers){
    //Locate the rows to be deleted, move them to array toDelete
    std::vector< std::vector<int> > toDelete(24, std::vector<int>(12,0));
    std::copy(currentLevel.begin(), currentLevel.end(), toDelete.begin()); //Copy current level-state

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
            //Move back one step on delete as lines changes
            i++;
        }
    }
    std::copy(toDelete.begin(), toDelete.end(), currentLevel.begin()); //Copy the new vector back to current level state
}

/*
 * Check for complete rows - store in std::vector lineNumbers and call deleteRows
 */
void Game::checkRows(){
    std::vector<int> lineNumbers(5, -1);
    bool completeRow;
    bool aRowIsFilled = false;
    int j, filledRow = 0;
    for (int i = 0; i < Game::LEVELROW; i++){
        completeRow = true;
        j = 0;
        while (completeRow){
            if (currentLevel[i][j] == 0){
                completeRow = false;
            } else{
                j++;
            }
            if (j == Game::LEVELCOL){
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
        deleteRows(lineNumbers); //Pass any filled rows to delete function
    }
}

void Game::movePiece(Game::Direction direction){
    switch (direction){
        case UP:
            if(isMovementAllowed(UP)) {
                p->setY(p->getX() + -1);
            }
            break;
        case DOWN:
            if(isMovementAllowed(DOWN)) {
                p->setY(p->getX() + 1);
            }else{
                combineVectors();
                checkRows();
                //Switch p and np after rows are checked
                delete p;
                p = np;
                p->randomizeRotation();
                p->setY(0);
                p->setX(4);
                np = pieceFactory->getRandomPiece();
            }
            break;
        case LEFT:
            if(isMovementAllowed(LEFT)) {
                p->setX(p->getY() + -1);
            }
            break;
        case RIGHT:
            if(isMovementAllowed(RIGHT)) {
                p->setX(p->getY() + 1);
            }
            break;
        default:
            break;
    }
}

void Game::combineVectors(){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (p->getThisRotation()[i][j] > 0){
                currentLevel[p->getX() + i][p->getY() + j] = p->getThisRotation()[i][j];
            } else{
            }
        }
    }
}

bool Game::isMovementAllowed(Direction direction){
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (p->getThisRotation()[i][j] > 0){
                switch (direction)
                {
                    case UP:
                        break;
                    case DOWN:
                        //Check for bottom
                        if (i + 1 + p->getX() > 23){ //TODO static value
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
                        if (j + p->getY() + 1 > 11) {//TODO static value
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


void Game::updateKey(SDL_KeyboardEvent *key){
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
            delete p; //TODO Delete
            p = np; //TODO Delete
            p->randomizeRotation(); //TODO Delete
            p->setY(0); //TODO Delete
            p->setX(4); //TODO Delete
            np = pieceFactory->getRandomPiece(); //TODO Delete
            break;

        case SDLK_SPACE:
            //p->rotateLeft();
            p->rotateRight();
            break;

        default:
            break;
    }
}
