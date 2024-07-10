#include <sstream>
#include "cli.h"

/* ---------------------------------------------------------------------------- */

namespace INTERPRETER
{
    std::unordered_map<std::string, bool*> SET_BOOL_VARIABLES = {
        {"capture_the_king", &CONFIG::capture_the_king},
        {"game_of_points", &CONFIG::game_of_points},
        {"play_for_mate", &CONFIG::play_for_mate},
        {"allow_passing", &CONFIG::allow_passing},
        {"any_capture", &CONFIG::any_capture},
        {"no_enpassant", &CONFIG::no_enpassant},
        {"sideways", &CONFIG::sideways},
        {"torpedo", &CONFIG::torpedo},
        {"zombies", &CONFIG::zombies},
    };

    std::unordered_map<std::string, int*> SET_INT_VARIABLES = {
        {"opposite_multiplier", &CONFIG::opposite_multiplier},
        {"time_control_value", &CONFIG::time_control_value},
        {"points_for_mate", &CONFIG::points_for_mate},
        {"promotion_rank", &CONFIG::promotion_rank},
        {"home_rank", &CONFIG::home_rank},
        {"base_time", &CONFIG::base_time},
    };
};

/* ---------------------------------------------------------------------------- */

void CLI::run()
{
    std::string command;
    
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command);
        process(command);
    }
}

/* ---------------------------------------------------------------------------- */

void CLI::process(const std::string& command)
{
    std::istringstream iss(command);

    std::string token;

    iss >> token;
    if (token == "exit") std::exit(EXIT_SUCCESS);

    else if (token == "set")
    {
        iss >> token;
        if (isSetBool(token))
        {
            std::string value;
            iss >> value;
            if (value == "true" || value == "1") *INTERPRETER::SET_BOOL_VARIABLES[token] = true;
            if (value == "false" || value == "0") *INTERPRETER::SET_BOOL_VARIABLES[token] = false;
        }

        else if (isSetInt(token))
        {
            int value;
            iss >> value;
            *INTERPRETER::SET_INT_VARIABLES[token] = value;
        }
    }

    else if (token == "print")
    {
        iss >> token;
        if (token == "config") CONFIG::print();
    }

    else 
    {
        std::cout << "Invalid action!" << std::endl;
    }
}

/* ---------------------------------------------------------------------------- */