#include "../utils/constants.h"

class Board
{
    public:
        int Pieces[196];
        int Players[196];
        int Royals[5];
        int Enpassant[5];
        int CastleRights;
        int Turn;

        MoveList getAllMoves();
        bool makeMove(const int& move);

    private:

        void placePiece(const int& square, const int& piece, const int& player);
        void removePiece(const int& square);
        
        bool isOpponentsPiece(const int& square, const int& player);

        bool isSquareAttacked(const int& square, const int& player);
        bool isKingChecked(const int& player);

        // Keys are used to read from pre_calculated moves

        int PawnKey(const int& square);
        int KnightKey(const int& square);
        int KingKey(const int& square);

        int BishopKey(const int& square);
        int RookKey(const int& square);
        int QueenKey(const int& square);
        
};