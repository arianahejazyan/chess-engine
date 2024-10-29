#include "definitions.h"
#include "config.h"

using namespace definitions;

#define iterate_crawl  for (Square sq = 0; sq < board_size; ++sq) for (Piece piece: {King, Knight})
#define iterate_slide2  for (Square sq = 0; sq < board_size; ++sq) for (Offset offset: patterns[Queen])
#define iterate_march  for (Square sq = 0; sq < board_size; ++sq) for (Player player: {Red, Blue, Yellow, Green})
#define iterate_castle for (Square sq = 0; sq < board_size; ++sq) for (Side side: {KingSide, QueenSide})


struct Pseudo
{
    vector<Square> crawl[board_size][2];
    vector<Square> slide[board_size][8];

    //vector<Square> push[board_size][player_size];
    //vector<Square> advance[board_size][player_size];

    //vector<Square> castle[player_size][side_size]; 
    //vector<Square> passing[player_size][side_size]; 
    //vector<Square> secure[player_size][side_size];

    void init(Config config);
};
/*
namespace pseudo
{
    // sq piece offset
    // sq piece offset
    
    vector<Square> crawl_squares[board_size][2]; // [square][piece]
    vector<Square> slide_squares[board_size][8]; // [square][offset]

    vector<Square> push_squares[board_size][player_size];
    vector<Square> advance_squares[board_size][player_size];

    vector<Square> castle_squares[player_size][side_size]; 
    vector<Square> passing_squares[player_size][side_size]; 
    vector<Square> secure_squares[player_size][side_size];

    void precalculate_all_squares();

    void precalculate_crawl_squares(Piece piece);


    // std::vector<Move> precalculated_push_moves[160][4]; // [square][player]
    // std::vector<Move> precalculated_double_push_moves[160][4]; // [square][player]
    // std::vector<Move> precalculated_advance_moves[160][4]; // [square][player]

    // std::vector<Move> march_moves[160][6];

    // void calculate_moves(Piece piece);

    // void calculate_all_moves();

    // void calculate_crawl_moves(const Square origin, const Piece piece, const Offset offset);


    // void calculate_march_moves(const Square sq, const Piece piece, const Direction& dir);


    // void calculate_promote_moves();

}; // namespace*/

/*

#pragma once
#include "definitions.h"

typedef unsigned int Hash;



#define hashPlayer(player) (player)
#define hashPlayerSide(player, side) (player << Config::SIDE_BITS ^ side)

#define hashSquareOffset(square, offset) (0)
#define hashPieceOffsetFlag(piece, offset, flag) (0)
#define hashSquareFlag(square, flag) (0) // OFFSETS
#define hashSquarePlayerFlag(square, player, flag) (0) // OFFSETS

inline Hash hash(); 
inline Hash hash(Square sq, Piece piece); 
inline Hash hash(Square sq, Piece piece, Ray ray); 
inline Hash hash(Square sq, Piece piece, Player player, Flag flag); 


namespace LookupTable
{
    std::vector<Move> PSEUDO_LEAP[BOARD_SIZE][PIECE_SIZE];
    std::vector<Move> PSEUDO_SLIDE[BOARD_SIZE][PIECE_SIZE][OFFSETS];
    std::vector<Move> PSEUDO_PUSH[BOARD_SIZE][PIECE_SIZE][PLAYERS];
    std::vector<Move> PSEUDO_ADVANCE[BOARD_SIZE][PIECE_SIZE][PLAYERS];



    extern std::unordered_map<Hash, std::vector<Move>> PSEUDO_LEGAL;


    extern std::unordered_map<Hash, std::vector<Square>> SECURE_SQUARES, PASSING_SQUARES;

   
    extern std::unordered_map<Hash, Square> s;


    extern Square *KING_INITIAL, **KING_FINAL, **ROOK_INITIAL, **ROOK_FINAL;


    extern std::unordered_map<Hash, std::vector<Ray>> RAY;

    extern std::unordered_map<Hash, std::vector<std::pair<Square, Offset>>> OFFSETS;


    // contains all leap offsets //
    extern std::vector<std::pair<Offset, Square>> LEAP_OFFSETS[CONSTANTS::BOARD_SIZE];

    // contains all slide offsets //
    extern std::vector<Offset> SLIDE_OFFSETS[BOARD::BOARD_SIZE];
    extern std::unordered_map<Offset, std::vector<Square>> SLIDE_RAY[BOARD::BOARD_SIZE];

    // contains all advance offsets //
    extern std::vector<std::pair<Offset, Square>> ADVANCE_OFFSETS[BOARD::BOARD_SIZE][PLAYER::MAX_PLAYERS];

  
    extern std::unordered_map<Hash, bool> VALID_PIECE;


    std::unordered_map<Square, std::vector<Square>> BLAST_AREA;



    void initialize();
};

*/