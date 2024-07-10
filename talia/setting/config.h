#pragma once
#include <vector>
//#include "piece.h"

/* ---------------------------------------------------------------------------- */

enum TimeControl {Increament, Delay};

enum StaleMate {Draw, Win, Lose};

enum Setup {FFA, RB, RY, RG};

//enum Mode {4PC, 2PC};

/* ---------------------------------------------------------------------------- */

namespace CONFIG
{
    extern bool capture_the_king;
    extern bool game_of_points;
    extern bool allow_passing;
    extern bool play_for_mate;
    extern bool any_capture;
    extern bool no_enpassant;
    extern bool sideways;
    extern bool torpedo;
    extern bool zombies;
    
    extern int opposite_multiplier;
    extern int time_control_value;
    extern int points_for_mate;
    extern int promotion_rank;
    extern int home_rank;
    extern int base_time;

    // StaleMate stalemate;
    
    
    // TimeControl time_control;
    

    // Setup setup;

    void print();
};

/* ---------------------------------------------------------------------------- */