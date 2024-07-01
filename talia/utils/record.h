#pragma once
#include "position.h"

/* ---------------------------------------------------------------------------- */

struct Record
{
    int depth;
    int nodes;
    int captures;
    int enpassants;
    int castles;
    int promotions;
    int checks;
    int multi_checks;
    int discovery_checks;
    int checkmates;
    int stalemates;
    int pass;

    Record();

    Record(int depth);

    ~Record();
};

/* ---------------------------------------------------------------------------- */

namespace RECORD
{
    void display(const Record& record);

    /********************************************************************************/

    inline void updateRecord(const std::vector<Position>& list, Record& record);

    inline void updateRecord(const Position& pos, Record& record);
};

/* ---------------------------------------------------------------------------- */