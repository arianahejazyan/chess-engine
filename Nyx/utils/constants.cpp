#include "constants.h"

void init_valid_squares()
{
    VALID_SQUARES.clear();
    
    for (int sq = 0; sq < ROWSIZE * COLSIZE; sq++)
    {
        if (config.bricks[sq] != Brick)
        {
            VALID_SQUARES.push_back(static_cast<Square>(sq));
        }
    }
}