TPiece.cpp//
// Created by larsson on 2017-01-30.
//

#include "../headers/Pieces/SPiece.h"

TPiece::TPiece() {
    representation =
            {
                    {
                            { 0, 0, 0, 0 },
                            { 0, 4, 4, 0 },
                            { 4, 4, 0, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 4, 0, 0, 0 },
                            { 4, 4, 0, 0 },
                            { 0, 4, 0, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 4, 4, 0 },
                            { 4, 4, 0, 0 },
                            { 0, 0, 0, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 4, 0, 0 },
                            { 0, 4, 4, 0 },
                            { 0, 0, 4, 0 },
                            { 0, 0, 0, 0 }
                    }
            };
    randomizeRotation();
}

TPiece::~TPiece() {}