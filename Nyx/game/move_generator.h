#include "../utils/definitions.h"
#include "../utils/constants.h"
#include "../utils/utils.h"

using namespace CONSTANTS;

class MoveGenerator
{
    public:

        void generate_all_moves(const Position& pos, vector<int>& move_list);

    protected:

        void generate_king_moves(const Position& pos, const Square& sq, vector<int>& move_list);

        void generate_queen_moves(const Position& pos, const Square& sq, vector<int>& move_list);

        void generate_rook_moves(const Position& pos, const Square& sq, vector<int>& move_list);

        void generate_bishop_moves(const Position& pos, const Square& sq, vector<int>& move_list);

        void generate_knight_moves(const Position& pos, const Square& sq, vector<int>& move_list);

        void generate_pawn_moves(const Position& pos, const Square& sq, vector<int>& move_list);

        /* ---------------------------------------------------------------------------- */

        void add_move(const Position& pos, int move, vector<int>& move_list);
};