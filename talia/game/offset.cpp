#include "offset.h"

/* ---------------------------------------------------------------------------- */

Direction::Direction(Offset rank, Offset file, Color player, Flag flag): rank(rank), file(file), player(player), flag(flag) {}

/* ---------------------------------------------------------------------------- */

Offset operator*(int count, Offset offset)
{
    return static_cast<Offset>(count * offset);
}

Offset operator*(Offset offset, int count)
{
    return count * offset;
}

/* ---------------------------------------------------------------------------- */