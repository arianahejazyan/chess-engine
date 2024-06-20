#pragma once
#include "board.h"
#include "player.h"
#include "piece.h"

/* ---------------------------------------------------------------------------- */

enum GameState {ongoing, over};

/* ---------------------------------------------------------------------------- */

struct Position
{
    Color turn;
    Piece pieces[BOARD::BOARD_SIZE];
    Color players[BOARD::BOARD_SIZE];  
    Square royals[PLAYER::MAX_PLAYERS];
    Square marked[PLAYER::MAX_PLAYERS];
    Square target[PLAYER::MAX_PLAYERS];
    bool kingSide[PLAYER::MAX_PLAYERS];
    bool queenSide[PLAYER::MAX_PLAYERS];
    unsigned short safty[PLAYER::MAX_PLAYERS];
    bool alive[PLAYER::MAX_PLAYERS];

    Position();

    Position(const Position& pos);

    ~Position();
};

/* ---------------------------------------------------------------------------- */

namespace POSITION
{
    GameState state();
};

/* ---------------------------------------------------------------------------- */