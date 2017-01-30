//
// Created by johan eriksson on 30/01/2017.
//

#ifndef SDLGAME_OLDPIECES_H
#define SDLGAME_OLDPIECES_H

#import <vector>

// Constant for pieces
enum PieceID{
    G_PIECE_I,
    G_PIECE_O,
    G_PIECE_T,
    G_PIECE_S,
    G_PIECE_Z,
    G_PIECE_L,
    G_PIECE_IL,
    G_PIECE_COUNT
};

// Constant for directions
enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ROTATE
};

class oldPieces {
private:
    int updatePiece(Pieces* p, int rotation);
    bool rotationVerifier(int rotation);
    PieceID randomisePiece();
    int randomiseRotation();
    //std::vector< std::vector<int> > thisPiece;//(4, std::vector<int>(4));
    //std::vector< std::vector<int> > nextPiece;//(4, std::vector<int>(4));

public:
    PieceID pieceName;
    Direction direction;

    int posX;
    int posY;
    int rotation;
    int leftEdge;
    int rightEdge;

    std::vector< std::vector<int> > thisPiece;
    std::vector< std::vector<int> > nextPiece;

    //Prototypes
    Pieces();
    ~Pieces();
    void destroyPiece(Pieces* p);
    static void rotatePiece(Pieces* p);

    static void testPiece();
    static void printPiece(Pieces* p);
};


#endif //SDLGAME_OLDPIECES_H
