#include <iostream>
#include <chrono>
#include <vector>
//#include "generator.h"
//#include "move.h"
//#include "position.h"
//#include "record.h"

using namespace std;
using namespace std::chrono;

/* ---------------------------------------------------------------------------- */

int preft(const Position& pos, int depth, int& nodes, int& time)
{
    if (depth != 0)
    {
        vector<Position> list;

        auto start = high_resolution_clock::now();

        generator.generate_all_positions(pos, list);

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);

        time += duration;

        nodes += list.size();

        for (const Position& child: list)
        {
            if (GameState == ongoing) preft(child, depth - 1, time);
        }
    }
}

/* ---------------------------------------------------------------------------- */

int main()
{
    Position pos = Position::Standard();

    int depth=10, nodes=1, time=0;

    preft(pos, depth, nodes, time);

    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Nodes: " << nodes << std::endl;
    std::cout << "Time: " << time << std::endl;
    std::cout << "Nps: " << nodes/time << std::endl;

    return 0;
}

/* ---------------------------------------------------------------------------- */