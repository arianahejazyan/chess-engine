#include "definitions.h"

using namespace definitions;

namespace parser
{
    char lower(char ch);

    bool is_integer(const string& str);
    
    vector<string> split_string(const string& fen, char delimiter);

    vector<string> split_board(const string& board);

    string substring(string str, char start, char end);

    bool parse_digit(char ch, int& digit);

    bool parse_integer(string str, int& integer);

    bool parse_location(string loc, Square& sq);

    bool parse_piece(char ch, Piece& piece);

    bool parse_player(char ch, Player& player);

    bool parse_turn(string turn, Position& pos);

    bool parse_state(Position& pos, string state);

    bool parse_right(Position& pos, string right, Side side);

    // parse score

    bool parse_fifty_rule(Position& pos, string fifty_rule);

    // parse royal

    bool parse_enpassant(string enpassant, Position& pos);

    bool parse_board(const string& board, Position& pos);

    bool parse_fen(string fen, Position& pos);
};