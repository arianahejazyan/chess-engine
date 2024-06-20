#include "board.h"

/* ---------------------------------------------------------------------------- */

void BOARD::initValidSquares()
{
    for (int sq = 0; sq < BOARD_SIZE; sq++)
    {
        if (bricks[sq] == false) VALID_SQUARES.push_back(static_cast<Square>(sq));
    }
}

bool BOARD::isPromotionSquare(const Square& sq, const Color& player)
{
    switch (player)
    {
        case (Red):    return Rank(sq) == PROMOTION_RANK;
        case (Blue):   return File(sq) == PROMOTION_RANK;
        case (Yellow): return Rank(sq) == MAX_RANK - PROMOTION_RANK;
        case (Green):  return File(sq) == MAX_FILE - PROMOTION_RANK;

        default: return false;
    }
}

bool BOARD::isHomeRankSquare(const Square& sq, const Color& player)
{
    switch (player)
    {
        case (Red):    return Rank(sq) == HOME_RANK;
        case (Blue):   return File(sq) == HOME_RANK;
        case (Yellow): return Rank(sq) == MAX_RANK - HOME_RANK;
        case (Green):  return File(sq) == MAX_FILE - HOME_RANK;

        default: return false;
    }
}

bool BOARD::isValidSquare(int r, int f)
{
    if (r < 0) return false;
    if (f < 0) return false;
    if (r > MAX_RANK) return false;
    if (f > MAX_FILE) return false;
    
    return bricks[Tile(r,f)] == false;
}

/* ---------------------------------------------------------------------------- */