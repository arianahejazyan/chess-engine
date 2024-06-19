#pragma once
#include "player.h"

/* ---------------------------------------------------------------------------- */

enum Offset {S=0, U=1, R=1, D=-1, L=-1};

enum Flag {Null=0, Push=1, DoublePush=2, SideWays, Advance=4, Enpassant=8, Promotion=16, Leap=32, Slide=64, Castle=128, Capture=256, Check=512};

enum Side {Neither=0, KingSide=1, QueenSide=2};

struct Ray
{
    Offset rank;
    Offset file;
};

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
    const int MAX_OFFSETS = 5;
};