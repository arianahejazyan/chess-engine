#include "../utils/definitions.h"

class Board
{
    public:

        bool make_move(Position& pos, const Move& move);

    protected:

        void place(Position& pos, const Square& sq, const Piece& piece, const Color& player);

        void remove(Position& pos, const Square& sq);

        void destroy(Position& pos, const Square& sq);

        void explosion(Position& pos, const Square& sq);

        bool isRoyalcheck(const Position& pos);
};

namespace
{
    Board board;
};