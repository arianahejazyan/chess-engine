#include "../utils/include/definitions.h"

class MoveGenerator
{
    public:

        void generate_all_moves(const Position& pos, vector<Move>& move_list);

    private:

        void generate_moves(const Position& pos, const Square& sq, vector<Move>& move_list);

        void leap(const Position& pos, const Square& sq, vector<Move>& move_list);

        void slide(const Position& pos, const Square& sq, vector<Move>& move_list);

        void push(const Position& pos, const Square& sq, vector<Move>& move_list);

        void advance(const Position& pos, const Square& sq, vector<Move>& move_list);

        void castle(const Position& pos, vector<Move>& move_list);

        void pass(vector<Move>& move_list);

        /* ---------------------------------------------------------------------------- */

        void add_move(const Position& pos, Move move, vector<Move>& move_list);
};