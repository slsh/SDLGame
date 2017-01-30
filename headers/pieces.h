//
// Created by johan eriksson on 26/01/2017.
//

#ifndef SDLGAME_PIECES_H
#define SDLGAME_PIECES_H

#import <vector>
#import "position.h"
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

class Pieces {
private:
    PieceID pieceName;
    Position position;
    std::vector< std::vector<int> > thisPiece;
    int rotation;
    int Pieces::randomiseRotation();

public:
    Pieces(PieceID pieceID);
    ~Pieces();

    static Pieces getThisRotation();
    static Pieces getNextRotation();
    static Pieces getLastRotation();

    static void testPiece();
    static void printPiece(Pieces* p);

};

#endif //SDLGAME_PIECES_H






