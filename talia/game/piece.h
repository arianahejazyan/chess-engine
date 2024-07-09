#pragma once
#include <vector>
#include <unordered_map>
#include <initializer_list>
#include <cmath>
#include "offset.h"

/* ---------------------------------------------------------------------------- */

enum Piece {Brick=-1, Empty=0, King=1, Queen=2, Rook=3, Bishop=4, Knight=5, Pawn=6};

/* ---------------------------------------------------------------------------- */

struct Direction
{
    Offset rank;
    Offset file;
    Color player;
    Flag flag;

    Direction(Offset rank, Offset file, Color player, Flag flag);
};


/* ---------------------------------------------------------------------------- */

namespace PIECE
{
    // total number of pieces
    constexpr int MAX_PIECES = 6;

    // minimum number of bits to encode pieces
    const int PIECE_BITS = std::ceil(std::log2(MAX_PIECES));

    // piece definitions
    std::unordered_map<Piece, std::vector<Direction>> DIRECTIONS;

    // array of possible promotions
    std::vector<Piece> PROMOTION_LIST;

    /* array of available piecces */
    std::vector<Piece> PIECE_LIST;

    /* cc */
    std::unordered_map<Piece, bool> LEAPER;
    std::unordered_map<Piece, bool> SLIDER;
    std::unordered_map<Piece, bool> PUSHER;
    std::unordered_map<Piece, bool> ADVANCER;

    

    /********************************************************************************/

    void initPieceDirections();

    void initPromotionList(std::initializer_list<Piece> list);

    void initPieceList();
};

/* ---------------------------------------------------------------------------- */