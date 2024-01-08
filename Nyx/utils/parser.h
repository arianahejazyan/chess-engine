#include "definitions.h"

class Parser
{
    public:

        Position pos;
        Config config;
        Player players[4];

        void process(const string& fen);
        void convert();
};

namespace
{
    Parser parser;
};