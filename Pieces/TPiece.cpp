//
// Created by larsson on 2017-01-30.
//

#include "../headers/Pieces/TPiece.h"

TPiece::TPiece() {
    representation =
        {
            {
                { 0, 3, 0, 0 },
                { 3, 3, 3, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 3, 0, 0 },
                { 0, 3, 3, 0 },
                { 0, 3, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 0, 0, 0 },
                { 3, 3, 3, 0 },
                { 0, 3, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 3, 0, 0 },
                { 3, 3, 0, 0 },
                { 0, 3, 0, 0 },
                { 0, 0, 0, 0 }
            }
        };
    randomizeRotation();
}

TPiece::~TPiece() {}