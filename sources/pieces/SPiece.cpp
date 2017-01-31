//
// Created by larsson on 2017-01-30.
//

#include "../../headers/pieces/SPiece.h"

SPiece::SPiece() {
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

SPiece::~SPiece() {}