#pragma once
#include <unordered_map>
#include "board.h"
#include "piece.h"
#include "move.h"

/* ---------------------------------------------------------------------------- */

typedef int Key;

/* ---------------------------------------------------------------------------- */

#define hashPlayerSide(player, side) (player << OFFSET::SIDE_BITS ^ side)
#define hashSquarePiece(square, piece) (square << PIECE::PIECE_BITS ^ piece)
#define hashSquarePieceRay(square, piece, ray) (((square << PIECE::PIECE_BITS ^ piece) << OFFSET::RAY_BITS) ^ ray)
#define hashSquarePiecePlayer(square, piece, player) (((square << PIECE::PIECE_BITS ^ piece) << PLAYER::PLAYER_BITS) ^ player)

/* ---------------------------------------------------------------------------- */

namespace PSEUDO
{
    // contains all pseudo legal moves //
    std::unordered_map<Key, std::vector<Move>> LEAP;
    std::unordered_map<Key, std::vector<Move>> SLIDE;
    std::unordered_map<Key, std::vector<Move>> PUSH;
    std::unordered_map<Key, std::vector<Move>> ADVANCE;

    // contains all castle moves and related squares //
    std::unordered_map<Key, Move> CASTLE;
    std::unordered_map<Key, std::vector<Square>> SECURE_SQUARES;
    std::unordered_map<Key, std::vector<Square>> PASSING_SQUARES;

    std::unordered_map<Key, std::vector<Ray>> RAY;

    // contains all leap offsets //
    std::vector<std::pair<Offset, Square>> LEAP_OFFSETS[BOARD::BOARD_SIZE];

    // contains all slide offsets //
    std::vector<Offset> SLIDE_OFFSETS[BOARD::BOARD_SIZE];
    std::unordered_map<Offset, std::vector<Square>> SLIDE_RAY[BOARD::BOARD_SIZE];

    // contains all advance offsets //
    std::vector<std::pair<Offset, Square>> ADVANCE_OFFSETS[BOARD::BOARD_SIZE][PLAYER::MAX_PLAYERS];

    //  //
    std::unordered_map<Offset, bool> VALID_LEAP[PIECE::MAX_PIECES];
    std::unordered_map<Offset, bool> VALID_SLIDE[PIECE::MAX_PIECES];
    std::unordered_map<Offset, bool> VALID_ADVANCE[PIECE::MAX_PIECES];

    /********************************************************************************/

    void leap(const Square& sq, const Piece& piece, const Direction& dir);

    void slide(const Square& sq, const Piece& piece, const Direction& dir);

    void push(const Square& sq, const Piece& piece, const Direction& dir);

    void advance(const Square& sq, const Piece& piece, const Direction& dir);

    void promote(const Square& sq, const Square& loc, const Square& tile, const Piece& piece, const Direction& dir, const Flag& flag, std::unordered_map<Key, std::vector<Move>>& table);

    void castle();

    void init();
};

/* ---------------------------------------------------------------------------- */