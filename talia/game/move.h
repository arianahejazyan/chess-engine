#pragma once
#include "board.h"
#include "piece.h"
#include "player.h"

/* ---------------------------------------------------------------------------- */

struct Move
{
    Square from;
    Square to;
    Piece piece;
    Color player;
    Piece promotion;
    Square marked;
    Side side;
    Flag flag;

    Move();
    Move(const Square& from, const Square& to, const Piece& piece, Flag flag);
    Move(const Square& from, const Square& to, const Piece& piece, const Color& player, const Piece& promotion, const Square& marked, Flag flag);
};

/* ---------------------------------------------------------------------------- */