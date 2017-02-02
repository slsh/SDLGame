//
// Created by larsson on 2017-01-30.
//

#include "../../headers/pieces/SquarePiece.h"

SquarePiece::SquarePiece() {
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
}

SquarePiece::~SquarePiece() {}