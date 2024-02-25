#pragma once
#include "definitions.h"
#include "utils.h"

namespace CONSTANTS
{
    constexpr int ROW_SIZE = 14;
    constexpr int COL_SIZE = 14;

    constexpr int BOARD_SIZE = ROW_SIZE * COL_SIZE;

    pair<Piece, string> PIECE_NAMES[32] =
    {
        {Brick,         "X"},
        {empty,         " "},
        {King,          "K"},
        {Queen,         "Q"},
        {Rook,          "R"},
        {Bishop,        "B"},
        {Knight,        "N"},
        {Pawn,          "P"},
    };

    string ROW_NAMES[ROW_SIZE] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"};

    string COL_NAMES[COL_SIZE] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",  "k",  "l",  "m",  "n"};

    constexpr int FLAG_SIZE = 8;

    constexpr int SQUARE_SIZE = 8;

    /* ---------------------------------------------------------------------------- */

    vector<Square> VALID_SQUARES;

    void INIT_VALID_SQUARES();

    /* ---------------------------------------------------------------------------- */

    Offset PAWN_PUSH[4] = {U, R, D, L};

    Offset PAWN_ATTACKS[4][2] = {{U + R, U + L}, {R + U, R + D}, {D + R, D + L}, {L + U, L + D}};

    vector<Piece> PIECE_LIST;

    void INIT_PIECE_LIST;

    /* ---------------------------------------------------------------------------- */

    map<Piece, vector<Direction>> PIECE_DIRECTIONS;

    void INIT_PIECE_DIRECTIONS();

    map<Piece, int> PIECE_TYPE;

    map<int, vector<int>> LEAP_MOVES;
    map<int, vector<int>> SLIDE_MOVES;
    map<int, vector<int>> PUSH_MOVES;
    map<int, vector<int>> ATTACK_MOVES;
    map<int, vector<int>> CRAWL_MOVES;
    map<int, vector<int>> HOP_MOVES;
    map<int, vector<int>> CASTLE_MOVES;

    void GENERATE_MOVES(const Square& sq);

    void GENERATE_LEAP_MOVES(const Square& sq, const Piece& piece);

    void GENERATE_SLIDE_MOVES(const Square& sq, const Piece& piece);

    void GENERATE_PUSH_MOVES(const Square& sq, const Piece& piece);

    void GENERATE_ATTACK_MOVES(const Square& sq, const Piece& piece);

    void GENERATE_CRAWL_MOVES(const Square& sq, const Piece& piece);

    void GENERATE_HOP_MOVES(const Square& sq, const Piece& piece);

    void GENERATE_CASTLE_MOVES(const Square& sq, const Piece& piece);

    void GENERATE_PROMOTION_MOVES(const Square& sq, const Square& loc, const Color& player, const Flag& flag);
};