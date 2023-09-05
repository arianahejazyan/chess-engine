#include "../utils/constants.h"

struct Position
{
    Piece  Pieces[196];
    Player Players[196];
    Square Royals[5];
    Square En_passant[5];
    CastleRights CastleRights[5];
    Player Turn;
};

struct Move
{
    Square from;
    Square to;
    bool capture;
    Flag flag;
    Piece promotion;
    Square enpass;
    int side;
};

struct MoveList
{
    std::vector<Move> Checks;
    std::vector<Move> Captures;
    std::vector<Move> QuietMoves;
};

class Board
{
    public:

        Position position;
        MoveList moveList;

        void GenerateAllMoves();
        bool makeMove(const Move& move);

    private:

        // Board utility methods

        void placePiece(const Square& square, const Piece& piece, const Player& player);
        void removePiece(const Square& square);
        
        bool isOpponentsPiece(const Square& square, const Player& player);

        bool isSquareAttacked(const Square& square, const Player& player);
        bool isKingChecked(const Player& player);

        // Handling crawling pieces (pawn, knight, king) logic
        
        void GenerateCrawlingMoves(std::vector<Square> RelevantSquares[196], const Square& square);
        void GenerateCastlingMoves(const Square& square);

        void GeneratePawnMoves(const Square& square);
        void GenerateKnightMoves(const Square& square);
        void GenerateKingMoves(const Square& square);

        // Handling sliding pieces (bishop, rook, queen) logic

        void GenerateSlidingMoves(std::vector<Square> RelevantSquares[196][4], const Square& square);

        void GenerateBishopMoves(const Square& square);
        void GenerateRookMoves(const Square& square);
        void GenerateQueenMoves(const Square& square);
        
};