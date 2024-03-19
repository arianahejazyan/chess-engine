#include "../../utils/include/definitions.h"

class Board
{
    public:

        bool makeMove(Position& pos, const Move& move);

    protected:

        void place(Position& pos, const Square& sq, const Piece& piece, const Color& player);

        void remove(Position& pos, const Square& sq);

        /* ---------------------------------------------------------------------------- */

        bool isOpponentAttacker(const Position& pos, const Move& move);

        bool isSquareSafe(const Position& pos, const Square& sq);

        bool isPathSafe(const Position& pos, const vector<Square>& path);

        bool isPathEmpty(const Position& pos, const vector<Square>& path);
};