#include "board.h"

/* ---------------------------------------------------------------------------- */

void BOARD::initValidSquares()
{
    for (int sq = 0; sq < BOARDSIZE; sq++)
    {
        if (bricks[sq] == false) VALID_SQUARES.push_back(static_cast<Square>(sq));
    }
}

bool BOARD::isPromotionSquare(const Square& sq, const Color& player)
{
    switch (player)
    {
        case (Red):    return Rank(sq) == PROMOTIONRANK;
        case (Blue):   return File(sq) == PROMOTIONRANK;
        case (Yellow): return Rank(sq) == MAXRANK - PROMOTIONRANK;
        case (Green):  return File(sq) == MAXFILE - PROMOTIONRANK;

        default: return false;
    }
}

bool BOARD::isHomeRankSquare(const Square& sq, const Color& player)
{
    switch (player)
    {
        case (Red):    return Rank(sq) == HOMERANK;
        case (Blue):   return File(sq) == HOMERANK;
        case (Yellow): return Rank(sq) == MAXRANK - HOMERANK;
        case (Green):  return File(sq) == MAXFILE - HOMERANK;

        default: return false;
    }
}

bool BOARD::isValidSquare(int r, int f)
{
    if (r < 0) return false;
    if (f < 0) return false;
    if (r > MAXRANK) return false;
    if (f > MAXFILE) return false;
    
    return bricks[Tile(r,f)] == false;
}

/* ---------------------------------------------------------------------------- */