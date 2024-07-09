#pragma once
#include <vector>
#include "piece.h"

/* ---------------------------------------------------------------------------- */

enum TimeControl {Increament, Delay};

enum StaleMate {Draw, Win, Lose};

enum Setup {FFA, RB, RY, RG};

enum Mode {4PC, 2PC};

/* ---------------------------------------------------------------------------- */

namespace CONFIG
{
    bool allow_passing;
    bool sideways;
    bool torpedo;
    bool any_capture;
    bool capture_the_king;
    bool enpassant;
    bool play_for_mate; // ffa
    bool zombies; // ffa
    bool game_of_points; // 2pc

    int promotion_rank;

    int home_rank;
    StaleMate stalemate;
    int opposite_multiplier; // ffa
    int points_for_mate; // ffa
    TimeControl time_control;
    int time_control_value;

    Setup setup;

    void init();
};

/* ---------------------------------------------------------------------------- */