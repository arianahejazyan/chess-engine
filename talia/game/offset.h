#pragma once
#include "player.h"

/* ---------------------------------------------------------------------------- */

typedef int Ray;

enum Offset {S=0, U=1, R=1, D=-1, L=-1};

enum Flag {Null=0, Push=1, DoublePush=2, SideWays, Advance=4, Enpassant=8, Promotion=16, Leap=32, Slide=64, Castle=128, Capture=256, Check=512, Pass};

enum Side {Neither=-1, KingSide=0, QueenSide=1};

struct Direction
{
    Offset rank;
    Offset file;
    Color player;
    Flag flag;

    Direction(Offset rank, Offset file, Color player, Flag flag);
};

/* ---------------------------------------------------------------------------- */

Offset operator*(int count, Offset offset);

Offset operator*(Offset offset, int count);

/* ---------------------------------------------------------------------------- */

namespace OFFSET
{
    constexpr int MAX_OFFSETS = 5;

    constexpr int MAX_SIDE = 2;

    constexpr int RAY_BITS = 8;

    constexpr int SIDE_BITS = 2;
};

/* ---------------------------------------------------------------------------- */