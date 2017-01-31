//
// Created by larsson on 2017-01-30.
//

#include "../headers/Pieces/InvertedLPiece.h"

TPiece::TPiece() {
    representation =
            {
                    {
                            {0, 0, 0, 0},
                            {0, 0, 7, 0},
                            {0, 0, 7, 0},
                            {0, 7, 7, 0}
                    },

                    {
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 7, 0, 0},
                            {0, 7, 7, 7}
                    },

                    {
                            {0, 0, 0, 0},
                            {0, 7, 7, 0},
                            {0, 7, 0, 0},
                            {0, 7, 0, 0}
                    },

                    {
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 7, 7, 7},
                            {0, 0, 0, 7}
                    }
            };
    randomizeRotation();
}

TPiece::~TPiece() {}