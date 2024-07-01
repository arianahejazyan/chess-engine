#include <iostream>
#include "record.h"

/* ---------------------------------------------------------------------------- */

Record::Record() {}

Record::Record(int depth): depth(depth) {}

Record::~Record() = default;

/* ---------------------------------------------------------------------------- */

void RECORD::display(const Record& record)
{

}

inline void RECORD::updateRecord(const std::vector<Position>& list, Record& record)
{
    for (const Position& pos: list)
    {
        updateRecord(pos, record);
    }
}

inline void RECORD::updateRecord(const Position& pos, Record& record)
{
    record.nodes++;

    if (flag & Leap) record.leaps++;
    if (flag & Slide) record.slides++;
    if (flag & Push) record.pushes++;
    if (flag & Advance) record.advances++;
    if (flag & Enpassant) record.enpassants++;
    if (flag & Castle) record.castles;
    if (flag & Promotion) record.promotions;
    if (flag & Pass) record.pass++;
    if (flag & Capture) record.captures++;
    if (pos.safty == 1) record.checks++;
    if (pos.safty >= 2) record.multi_checks;
    if () record.discovery_checks++;
    if () record.checkmates++;
    if () record.stalemates++;
}

/* ---------------------------------------------------------------------------- */
