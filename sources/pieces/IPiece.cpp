//
// Created by larsson on 2017-01-30.
//

#include "../../headers/pieces/IPiece.h"

IPiece::IPiece() {
    representation =
            {
                    {
                            { 0, 1, 0, 0 },
                            { 0, 1, 0, 0 },
                            { 0, 1, 0, 0 },
                            { 0, 1, 0, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 1, 1, 1, 1 },
                            { 0, 0, 0, 0 },
                            { 0, 0, 0, 0 }
                    },

                    {
                            { 0, 1, 0, 0 },
                            { 0, 1, 0, 0 },
                            { 0, 1, 0, 0 },
                            { 0, 1, 0, 0 }
                    },

                    {
                            { 0, 0, 0, 0 },
                            { 1, 1, 1, 1 },
                            { 0, 0, 0, 0 },
                            { 0, 0, 0, 0 }
                    }
            };
    randomizeRotation();
}

IPiece::~IPiece() {}