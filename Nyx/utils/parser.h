#include "definitions.h"

class Parser
{
    public:

        Position parse(const string& fen);

        string convert(const Move& move);        
};

namespace
{
    Parser parser;
};