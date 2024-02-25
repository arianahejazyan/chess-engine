#include "../utils/definitions.h"
#include "../utils/constants.h"
#include "../utils/utils.h"

using namespace CONSTANTS;

class MoveGenerator
{
    public:

        void generate_all_moves(const Position& pos, vector<int>& move_list);

        void generate_moves(const Position& pos, const Square& sq, vector<int>& move_list);

    protected:

        void leap(const Position& pos, const Square& sq, vector<int>& move_list);

        void slide(const Position& pos, const Square& sq, vector<int>& move_list);

        void push(const Position& pos, const Square& sq, vector<int>& move_list);

        void attack(const Position& pos, const Square& sq, vector<int>& move_list);

        void castle(const Position& pos, vector<int>& move_list);

        void pass(vector<int>& move_list);

        /* ---------------------------------------------------------------------------- */

        void add_move(const Position& pos, int move, vector<int>& move_list);
};

namespace
{
    MoveGenerator move_generator;
}