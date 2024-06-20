#include "position.h"

/* ---------------------------------------------------------------------------- */

Position::Position() = default;

Position::Position(const Position& pos): turn(pos.turn)
{
    for (const Square& sq: BOARD::VALID_SQUARES)
    {
        pieces[sq] = pos.pieces[sq];
        players[sq] = pos.players[sq];
    }

    for (const Color& player: PLAYER::ALIVE_LIST)
    {
        royals[player] = pos.royals[player];
        marked[player] = pos.marked[player];
        target[player] = pos.target[player];
        kingSide[player] = pos.kingSide[player];
        queenSide[player] = pos.queenSide[player];
        safty[player] = pos.safty[player];
    }
}

Position::~Position() = default;

/* ---------------------------------------------------------------------------- */

GameState state()
{
    
}

/* ---------------------------------------------------------------------------- */