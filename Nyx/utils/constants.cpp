#include "constants.h"

void init_bishop_relevant_squares(std::vector<int> BishopRelevantSquares[196][4])
{   
    for (int square = 0; square < 196; square++)
    {

        int r, f;

        for (r = rank(square) + 1, f = file(square) + 1; r <= 13 && f <= 13; r++, f++) 
        {
            if (isInvalidSquare(r, f)) break;

            BishopRelevantSquares[square][0].push_back(r * 14 + f);
        }

        for (r = rank(square) - 1, f = file(square) + 1; r >= 0 && f <= 13; r--, f++) 
        {
            if (isInvalidSquare(r, f)) break;

            BishopRelevantSquares[square][1].push_back(r * 14 + f);
        }

        for (r = rank(square) - 1, f = file(square) - 1; r >= 0 && f >= 0; r--, f--) 
        {
            if (isInvalidSquare(r, f)) break;

            BishopRelevantSquares[square][2].push_back(r * 14 + f);
        }

        for (r = rank(square) + 1, f = file(square) - 1; r <= 13 && f >= 0; r++, f--) 
        {
            if (isInvalidSquare(r, f)) break;

            BishopRelevantSquares[square][3].push_back(r * 14 + f);
        }
    }
}

void init_rook_relevant_squares(std::vector<int> RookRelevantSquares[196][4])
{   
    for (int square = 0; square < 196; square++)
    {

        int r, f;

        for (r = rank(square) + 1; r <= 13; r++) 
        {
            if (isInvalidSquare(r, f)) break;

            RookRelevantSquares[square][0].push_back(r * 14 + f);
        }

        for (f = file(square) + 1; f <= 13; f++) 
        {
            if (isInvalidSquare(r, f)) break;

            RookRelevantSquares[square][1].push_back(r * 14 + f);
        }

        for (r = rank(square) - 1; r >= 0; r--) 
        {
            if (isInvalidSquare(r, f)) break;

            RookRelevantSquares[square][2].push_back(r * 14 + f);
        }

        for (f = file(square) - 1; f >= 0; f--) 
        {
            if (isInvalidSquare(r, f)) break;

            RookRelevantSquares[square][3].push_back(square + r * 14 + f);
        }
    }
}

void init_king_relevant_squares(std::vector<int> KingRelevantSquares[196])
{   
    for (int square = 0; square < 196; square++)
    {
        int r = rank(square), f = file(square);

        if (isInvalidSquare(r, f)) continue;

        if (r <= 12           ) if (isInvalidSquare(r + 1, f    )) KingRelevantSquares[square].push_back(square + 14); // up
        if (r <= 12 && f <= 12) if (isInvalidSquare(r + 1, f + 1)) KingRelevantSquares[square].push_back(square + 15); // up-right
        if (           f <= 12) if (isInvalidSquare(r    , f + 1)) KingRelevantSquares[square].push_back(square + 1 ); // right
        if (r >= 1  && f <= 12) if (isInvalidSquare(r - 1, f + 1)) KingRelevantSquares[square].push_back(square - 13); // down-right
        if (r >= 1            ) if (isInvalidSquare(r - 1, f    )) KingRelevantSquares[square].push_back(square - 14); // down
        if (r >= 1  && f >= 1 ) if (isInvalidSquare(r - 1, f - 1)) KingRelevantSquares[square].push_back(square - 15); // down-left
        if (           f >= 1 ) if (isInvalidSquare(r    , f - 1)) KingRelevantSquares[square].push_back(square - 1 ); // left
        if (r <= 12 && f >= 1 ) if (isInvalidSquare(r + 1, f - 1)) KingRelevantSquares[square].push_back(square + 13); // up-left
    }
}

void init_knight_relevant_squares(std::vector<int> KnightRelevantSquares[196])
{   
    for (int square = 0; square < 196; square++)
    {
        int r = rank(square), f = file(square);

        if (isInvalidSquare(r, f)) continue;

        if (r <= 11 && f <= 12) if (isInvalidSquare(r + 2, f + 1)) KnightRelevantSquares[square].push_back(square + 29); // up-up-right
        if (r <= 12 && f <= 11) if (isInvalidSquare(r + 1, f + 2)) KnightRelevantSquares[square].push_back(square + 16); // up-right-right
        if (r >= 1  && f <= 11) if (isInvalidSquare(r - 1, f + 2)) KnightRelevantSquares[square].push_back(square - 12); // down-right-right
        if (r >= 2  && f <= 12) if (isInvalidSquare(r - 2, f + 1)) KnightRelevantSquares[square].push_back(square - 27); // down-down-right
        if (r >= 2  && f >= 1 ) if (isInvalidSquare(r - 2, f - 1)) KnightRelevantSquares[square].push_back(square - 29); // down-down-left
        if (r >= 1  && f >= 2 ) if (isInvalidSquare(r - 1, f - 2)) KnightRelevantSquares[square].push_back(square - 16); // down-left-left
        if (r <= 12 && f >= 2 ) if (isInvalidSquare(r + 1, f - 2)) KnightRelevantSquares[square].push_back(square + 12); // up-left-left
        if (r <= 11 && f >= 1 ) if (isInvalidSquare(r + 2, f - 1)) KnightRelevantSquares[square].push_back(square + 27); // up-up-left
    }
}