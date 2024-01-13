#pragma once
#include "definitions.h"

namespace CONSTANTS
{
    constexpr int ROWSIZE = 14;
    constexpr int COLSIZE = 14;

    constexpr int MAXRANK = ROWSIZE - 1;
    constexpr int MAXFILE = COLSIZE - 1;

    map<Piece, string> PIECE_TO_STRING;

    map<string, Piece> STRING_TO_PIECE;

    map<Square, string> SQUARE_TO_STRING;

    vector<Square> VALID_SQUARES;

    vector<Piece> PIECE_LIST;

    map<Piece, vector<int>> PIECE_DIRECTIONS;

    map<Piece, vector<Offset>> PIECE_RAYS;

    void init();

    void init_piece_to_string();

    void INIT_STRING_TO_PIECE();
};