#include "definitions.h"

using namespace definitions;

namespace parser
{
    bool is_integer(const string& str);
    
    vector<string> split_string(const string& fen, char delimiter);

    vector<string> split_board(const string& board);

    bool parse_piece(char ch, Piece& piece);

    bool parse_player(char ch, Player& player);

    bool parse_board(const string& board, Position& pos);

    // bool parse_turn(const string& turn, Position& pos);

    //bool parse_right(const string& right, const Side& side, Position& pos);

    //bool parse_enpassant(const string& enpassant, Position& pos);

    // bool parse_fen(const string& fen, Position& pos);
};