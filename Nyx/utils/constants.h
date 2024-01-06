#pragma once
#include "definitions.h"

namespace
{
    constexpr int ROWSIZE = 14;
    constexpr int COLSIZE = 14;

    constexpr int MAXRANK = ROWSIZE - 1;
    constexpr int MAXFILE = COLSIZE - 1;

    vector<Square> VALID_SQUARES;

    vector<Piece> PIECE_LIST;

    map<Piece, vector<int>> PIECE_DIRECTIONS;

    map<Piece, vector<Offset>> PIECE_RAYS;
};

void init_valid_squares();