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
    Square midway;
    Side side;
    Flag flag;

    Move();
};

/* ---------------------------------------------------------------------------- */