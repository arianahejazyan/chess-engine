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

namespace pseudo
{

extern unsigned int KING_MOVEMENT;
extern unsigned int KNIGHT_MOVEMENT;

extern unsigned int QUEEN_MOVEMENT[8];
extern unsigned int ROOK_MOVEMENT[4];
extern unsigned int BISHOP_MOVEMENT[4];


void crawl(Piece piece, unsigned int& idx, unsigned int movement);

void slide(Offset offset, unsigned int& idx, unsigned int movement);

// 2 crawl, 8 slide, 8 march, 8 castle
extern unsigned int start[board_size][26], range[board_size][26];

// all precalculated moves
extern array<Square, 100000> squares;

void initialize();

};