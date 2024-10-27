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

    string substring(string str, char start, char end);

    bool parse_digit(char ch, int& digit);

    bool parse_integer(string str, int& integer);

    bool parse_location(string loc, Square& sq);

    bool parse_enpassant(string enpassant, Position& pos);

    bool parse_turn(string turn, Position& pos);

    bool parse_right(string right, Side side, Position& pos);

    bool parse_fen(string fen, Position& pos);
};