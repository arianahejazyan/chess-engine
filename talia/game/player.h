#pragma once

/* ---------------------------------------------------------------------------- */

enum Color {None=-1, Red=0, Blue=1, Yellow=2, Green=3};

/* ---------------------------------------------------------------------------- */

struct Player
{
    Color color;
    int time;
    int points;
    bool state;

    Player(Color color): color(color) {}
};

/* ---------------------------------------------------------------------------- */

#define next(player) ((player + 1) % MAX_PLAYERS)

/* ---------------------------------------------------------------------------- */

namespace PLAYER
{
    constexpr int MAX_PLAYERS = 4;
    constexpr int PLAYER_BITS = 2;

    Player PLAYER_LIST[MAX_PLAYERS] = {Player(Red),Player(Blue),Player(Yellow),Player(Green)};

    constexpr Color COLOR_LIST[MAX_PLAYERS] = {Red, Blue, Yellow, Green};
    std::vector<Color> OPPONENT_LIST[MAX_PLAYERS];
    std::vector<Color> TEAMMATE_LIST[MAX_PLAYERS];

    bool TEAMMATE[MAX_PLAYERS][MAX_PLAYERS];
    bool OPPONENT[MAX_PLAYERS][MAX_PLAYERS];

    std::vector<Color> OTHERS[MAX_PLAYERS];
};

/* ---------------------------------------------------------------------------- */