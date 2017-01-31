//
// Created by larsson on 2017-01-30.
//

#include "../../headers/pieces/ZPiece.h"

ZPiece::ZPiece() {
    representation =
            {
                    {
                            { 0, 0, 0, 0 },
                            { 0, 5, 5, 0 },
                            { 0, 0, 5, 5 },
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

ZPiece::~ZPiece() {}