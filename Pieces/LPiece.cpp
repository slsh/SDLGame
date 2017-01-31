//
// Created by larsson on 2017-01-30.
//

#include "../headers/Pieces/LPiece.h"

TPiece::TPiece() {
    representation =
            {
                    {
                            { 0, 0, 0, 0 },
                            { 0, 6, 0, 0 },
                            { 0, 6, 0, 0 },
                            { 0, 6, 6, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 0, 0, 0, 0 },
                            { 6, 6, 6, 0 },
                            { 6, 0, 0, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 6, 6, 0, 0 },
                            { 0, 6, 0, 0 },
                            { 0, 6, 0, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 0, 0, 6, 0 },
                            { 6, 6, 6, 0 },
                            { 0, 0, 0, 0 }
                    }
            };
    randomizeRotation();
}

TPiece::~TPiece() {}