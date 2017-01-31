//
// Created by larsson on 2017-01-30.
//

#include "../headers/Pieces/SquarePiece.h"

TPiece::TPiece() {
    representation =
            {
                    {
                            { 0, 0, 0, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 2, 2, 0 },
                            { 0, 0, 0, 0 }
                    }
            };
    randomizeRotation();
}

TPiece::~TPiece() {}