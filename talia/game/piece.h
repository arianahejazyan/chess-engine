#pragma once
#include <vector>
#include <unordered_map>
#include <initializer_list>
#include "offset.h"

/* ---------------------------------------------------------------------------- */

enum Piece {Brick=-1, Empty=0, King=1, Queen=2, Rook=3, Bishop=4, Knight=5, Pawn=6};

/* ---------------------------------------------------------------------------- */

namespace PIECE
{
    constexpr int MAX_PIECES = 6;

    std::unordered_map<Piece, std::vector<Direction>> DIRECTIONS;

    std::vector<Piece> PROMOTION_LIST;

    std::vector<Piece> PIECE_LIST;

    std::unordered_map<Piece, bool> LEAPER;
    std::unordered_map<Piece, bool> SLIDER;
    std::unordered_map<Piece, bool> PUSHER;
    std::unordered_map<Piece, bool> ADVANCER;

    void initPieceDirections();

    void initPromotionList(std::initializer_list<Piece> list);

    void initPieceList();
};

/* ---------------------------------------------------------------------------- */