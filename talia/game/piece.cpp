#include "piece.h"

/* ---------------------------------------------------------------------------- */

void PIECE::initPieceDirections()
{
    PIECE::DIRECTIONS[King] = 
    {
        Direction(U, S, None, Leap),
        Direction(D, S, None, Leap),
        Direction(S, R, None, Leap),
        Direction(S, L, None, Leap),
        Direction(U, R, None, Leap),
        Direction(U, L, None, Leap),
        Direction(D, R, None, Leap),
        Direction(D, L, None, Leap),
    };

    PIECE::DIRECTIONS[Queen] = 
    {
        Direction(U, S, None, Slide),
        Direction(D, S, None, Slide),
        Direction(S, R, None, Slide),
        Direction(S, L, None, Slide),
        Direction(U, R, None, Slide),
        Direction(U, L, None, Slide),
        Direction(D, R, None, Slide),
        Direction(D, L, None, Slide),
    };

    PIECE::DIRECTIONS[Rook] = 
    {
        Direction(U, S, None, Slide),
        Direction(D, S, None, Slide),
        Direction(S, R, None, Slide),
        Direction(S, L, None, Slide),
    };

    PIECE::DIRECTIONS[Bishop] = 
    {
        Direction(U, R, None, Slide),
        Direction(U, L, None, Slide),
        Direction(D, R, None, Slide),
        Direction(D, L, None, Slide),
    };

    PIECE::DIRECTIONS[Knight] = 
    {
        Direction(2 * U, R, None, Leap),
        Direction(2 * U, L, None, Leap),
        Direction(U, 2 * R, None, Leap),
        Direction(U, 2 * L, None, Leap),
        Direction(2 * D, R, None, Leap),
        Direction(2 * D, R, None, Leap),
        Direction(D, 2 * R, None, Leap),
        Direction(D, 2 * L, None, Leap),
    };

    PIECE::DIRECTIONS[Pawn] = 
    {
        Direction(U, S, Red, Push),
        Direction(S, R, Red, SideWays),
        Direction(S, L, Red, SideWays),
        Direction(U, R, Red, Advance),
        Direction(U, L, Red, Advance),

        Direction(S, R, Blue, Push),
        Direction(U, S, Blue, SideWays),
        Direction(D, S, Blue, SideWays),
        Direction(U, R, Blue, Advance),
        Direction(D, R, Blue, Advance),

        Direction(D, S, Yellow, Push),
        Direction(S, R, Yellow, SideWays),
        Direction(S, L, Yellow, SideWays),
        Direction(D, R, Yellow, Advance),
        Direction(D, L, Yellow, Advance),

        Direction(S, L, Green, Push),
        Direction(U, S, Green, SideWays),
        Direction(D, S, Green, SideWays),
        Direction(U, L, Green, Advance),
        Direction(D, L, Green, Advance),
    };
}

void PIECE::initPromotionList(std::initializer_list<Piece> list)
{
    PIECE::PROMOTION_LIST = list;
}

void PIECE::initPieceList()
{

}

/* ---------------------------------------------------------------------------- */