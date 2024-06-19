#pragma once
#include <vector>
#include "position.h"
#include "move.h"

/* ---------------------------------------------------------------------------- */

namespace Generator
{
    void generate_all_positions(std::vector<Position>& list, const Position& pos);

    /********************************************************************************/

    inline static void leap(std::vector<Position>& list, const Position& pos, const Square& sq);

    inline static void slide(std::vector<Position>& list, const Position& pos, const Square& sq);

    inline static void push(std::vector<Position>& list, const Position& pos, const Square& sq);

    inline static void advance(std::vector<Position>& list, const Position& pos, const Square& sq);

    inline static void enpassant(std::vector<Position>& list, const Position& pos);

    inline static void castle(std::vector<Position>& list, const Position& pos);

    inline static void pass(std::vector<Position>& list, const Position& pos);

    /********************************************************************************/

    static void make_move(std::vector<Position>& list, const Position& pos, const Move& move);

    /********************************************************************************/

    inline static void place(Position& pos, const Square& sq, const Piece& piece, const Color& player);

    inline static void remove(Position& pos, const Square& sq);

    /********************************************************************************/

    inline static bool isRoyalSafe(const Position& pos);

    inline static bool isSquareSafe(const Position& pos, const Color& player);

    inline static unsigned short countRoyalChecks(Position& pos, const Color& player);

    inline static unsigned short attackedByLeap(const Position& pos, const Square& sq);

    inline static unsigned short attackedBySlide(const Position& pos, const Square& sq);

    inline static unsigned short attackedByAdvance(const Position& pos, const Square& sq);
};

/* ---------------------------------------------------------------------------- */