//
// Created by larsson on 2017-01-30.
//

#include "../headers/Pieces/ZPiece.h"

TPiece::TPiece() {
    representation =
            {
                    {
                            { 0, 0, 0, 0 },
                            { 5, 5, 0, 0 },
                            { 0, 5, 5, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 5, 0, 0 },
                            { 5, 5, 0, 0 },
                            { 5, 0, 0, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 5, 5, 0, 0 },
                            { 0, 5, 5, 0 },
                            { 0, 0, 0, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 0, 5, 0 },
                            { 0, 5, 5, 0 },
                            { 0, 5, 0, 0 },
                            { 0, 0, 0, 0 }
                    }
            };
    randomizeRotation();
}

TPiece::~TPiece() {}