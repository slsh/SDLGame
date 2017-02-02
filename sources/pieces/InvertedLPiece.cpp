//
// Created by larsson on 2017-01-30.
//

#include "../../headers/pieces/InvertedLPiece.h"

InvertedLPiece::InvertedLPiece() {
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
}

InvertedLPiece::~InvertedLPiece() {}