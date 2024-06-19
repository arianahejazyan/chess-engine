#pragma once
#include <unordered_map>
#include "board.h"
#include "piece.h"
#include "move.h"

/* ---------------------------------------------------------------------------- */

struct Key
{
    Square sq;
    Piece piece;
    Offset offset;
    Color player;
    Side side;
    
    Key(Square sq, Piece piece);
    Key(Square sq, Piece piece, Offset rank, Offset file);
    Key(Square sq, Piece piece, Color player);
};

/* ---------------------------------------------------------------------------- */

namespace PSEUDO
{
    std::unordered_map<Key, std::vector<Move>> LEAP;
    std::unordered_map<Key, std::vector<Move>> SLIDE;
    std::unordered_map<Key, std::vector<Move>> PUSH;
    std::unordered_map<Key, std::vector<Move>> ADVANCE;
    std::unordered_map<Key, Move> CASTLE;

    std::unordered_map<Key, std::vector<Move>> SECURE;
    std::unordered_map<Key, std::vector<Move>> PASSING;

    std::unordered_map<Key, std::vector<Offset>> RAY;



    // contains all leap offsets //
    std::vector<std::pair<Offset, Square>> LEAP_OFFSETS[BOARD::BOARDSIZE];

    // contains all slide offsets //
    std::vector<Offset> SLIDE_OFFSETS[BOARD::BOARDSIZE];
    std::unordered_map<Offset, std::vector<Square>> SLIDE_RAY[BOARD::BOARDSIZE];

    // contains all advance offsets //
    std::vector<std::pair<Offset, Square>> ADVANCE_OFFSETS[BOARD::BOARDSIZE][PLAYER::MAX_PLAYERS];

    //  //
    std::unordered_map<Offset, bool> VALID_LEAP[PIECE::MAX_PIECES];
    std::unordered_map<Offset, bool> VALID_SLIDE[PIECE::MAX_PIECES];
    std::unordered_map<Offset, bool> VALID_ADVANCE[PIECE::MAX_PIECES];

    

    


    


    void leap(const Square& sq, const Piece& piece, const Direction& dir);

    void slide(const Square& sq, const Piece& piece, const Direction& dir);

    void push(const Square& sq, const Piece& piece, const Direction& dir);

    void advance(const Square& sq, const Piece& piece, const Direction& dir);

    void promote(const Square& sq, const Square& loc, const Square& tile, const Piece& piece, const Direction& dir, const Flag& flag, std::unordered_map<Key, std::vector<Move>>& table);

    void castle();

    void init();
};

/* ---------------------------------------------------------------------------- */