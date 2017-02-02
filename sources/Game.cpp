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
    score = 0;
    highscore = 0;
}

void Game::init(){
    //Create initial two pieces
    p = pieceFactory->getRandomPiece();
    p->randomizeRotation();
    p->setY(0);
    p->setX(4);
    np = pieceFactory->getRandomPiece();
    if (score > highscore) {
        highscore = score;
    }
    score = 0;
}

// Basic tracker of automatic speed
unsigned long long Game::getScore(){
    if (score < 15000){
        return 2;
    } else if (score < 30000){
        return 3;
    } else if (score < 45000){
        return 4;
    } else if (score < 60000){
        return 5;
    } else if (score < 75000){
        return 6;
    } else if (score < 90000){
        return 7;
    } else if (score < 105000){
        return 8;
    } else if (score < 120000){
        return 9;
    } else if (score < 135000){
        return 10;
    } else if (score < 150000){
        return 15;
    } else if (score < 160000){
        return 20;
    }
    return 2;
}

void Game::updateWindow(){
    graphicManager->updateWindow(p, np,currentLevel);
}

void Game::close(){
    graphicManager->close();
}

void Game::deleteCompleteRows() {
    const std::vector<int> emptyRow(12, 0);
    int scoreMultiplier = 1;
    int deletedRows = 0;

    for (unsigned int rowNumber = 0; rowNumber < currentLevel.size(); rowNumber++) {
        if (isVectorFilled(currentLevel.at(rowNumber))) {
            currentLevel.erase(currentLevel.begin() + rowNumber);
            currentLevel.insert(currentLevel.begin(), emptyRow);
            deletedRows++;
            scoreMultiplier *= MULTIPLIER_FACTOR;
        }
    }

    if (deletedRows > 0) {
        score += ROW_POINTS * scoreMultiplier;
        std::cout << "Score: " << score << std::endl;
    }
}

bool Game::isVectorFilled(std::vector<int> v) {
    for (int val : v) {
        if (val == 0) {
            return false;
        }
    }
    return true;
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
                deleteCompleteRows();
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
