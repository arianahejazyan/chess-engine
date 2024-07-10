#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "config.h"

/* ---------------------------------------------------------------------------- */

class CLI
{
public:
    void run();

private:
    void process(const std::string& command);
};

/* ---------------------------------------------------------------------------- */

#define isSetBool(token) (INTERPRETER::SET_BOOL_VARIABLES.find(token) != INTERPRETER::SET_BOOL_VARIABLES.end())
#define isSetInt(token) (INTERPRETER::SET_INT_VARIABLES.find(token) != INTERPRETER::SET_INT_VARIABLES.end())

/* ---------------------------------------------------------------------------- */

namespace INTERPRETER
{
    extern std::unordered_map<std::string, bool*> SET_BOOL_VARIABLES;
    extern std::unordered_map<std::string, int*> SET_INT_VARIABLES;
};

/* ---------------------------------------------------------------------------- */