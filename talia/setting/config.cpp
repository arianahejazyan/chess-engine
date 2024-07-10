#include <iostream>
#include "config.h"

/* ---------------------------------------------------------------------------- */

namespace CONFIG 
{
    bool capture_the_king = false;
    bool game_of_points = false;
    bool allow_passing = false;
    bool play_for_mate = false;
    bool any_capture = false;
    bool no_enpassant = false;
    bool sideways = false;
    bool torpedo = false;
    bool zombies = false;
    
    int opposite_multiplier = 0;
    int time_control_value = 15;
    int points_for_mate = 20;
    int promotion_rank = 10;
    int home_rank = 1;
    int base_time = 60;
}

/* ---------------------------------------------------------------------------- */

void CONFIG::print()
{
    std::cout << "capture_the_king: " << capture_the_king << std::endl;
    std::cout << "game_of_points: " << game_of_points << std::endl;
    std::cout << "allow_passing: " << allow_passing << std::endl;
    std::cout << "play_for_mate: " << play_for_mate << std::endl;
    std::cout << "any_capture: " << any_capture << std::endl;
    std::cout << "no_enpassant: " << no_enpassant << std::endl;
    std::cout << "sideways: " << sideways << std::endl;
    std::cout << "torpedo: " << torpedo << std::endl;
    std::cout << "zombies: " << zombies << std::endl;
    
    std::cout << "opposite_multiplier: " << opposite_multiplier << std::endl;
    std::cout << "time_control_value: " << time_control_value << std::endl;
    std::cout << "points_for_mate: " << points_for_mate << std::endl;
    std::cout << "promotion_rank: " << promotion_rank << std::endl;
    std::cout << "home_rank: " << home_rank << std::endl;
    std::cout << "base_time: " << base_time << std::endl;
}

/* ---------------------------------------------------------------------------- */