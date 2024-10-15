#include "definitions.h"

namespace parser
{
    vector<string> split_string(const string& fen, char delimiter);

    vector<string> split_board(const string& board);

    // bool parse_turn(const string& turn, Position& pos);

    //bool parse_right(const string& right, const Side& side, Position& pos);

    //bool parse_enpassant(const string& enpassant, Position& pos);

    // bool parse_board(const string& board, Position& pos);

    // bool parse_fen(const string& fen, Position& pos);
};