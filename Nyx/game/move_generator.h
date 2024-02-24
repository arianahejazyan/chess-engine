#include "../utils/definitions.h"
#include "../utils/constants.h"
#include "../utils/utils.h"

class MoveGenerator
{
    public:

        void generate_all_moves(const Position& pos, vector<Move>& move_list);

    protected:

        void generate_king_moves(const Position& pos, const Square& sq, vector<Move>& move_list);

        void generate_queen_moves(const Position& pos, const Square& sq, vector<Move>& move_list);

        void generate_rook_moves(const Position& pos, const Square& sq, vector<Move>& move_list);

        void generate_bishop_moves(const Position& pos, const Square& sq, vector<Move>& move_list);

        void generate_knight_moves(const Position& pos, const Square& sq, vector<Move>& move_list);

        void generate_pawn_moves(const Position& pos, const Square& sq, vector<Move>& move_list);

        /* ---------------------------------------------------------------------------- */

        void add_move(const Position& pos, Move move, vector<Move>& move_list);
};