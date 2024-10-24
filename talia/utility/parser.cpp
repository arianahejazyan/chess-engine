#include <sstream>
#include "parser.h"
#include <iostream>

namespace parser
{
    
//int bricks[14] = {3,9,15,18,18,18,18,18,18,18,18,21,24,27};
//int stones[20] = {3,9,15, ..., 21,24,27};

//#define Spot(row, col) (row * dim + col - bricks[row])
//#define Rank(square) ((square + bricks[square / 8]) / dim)
//#define File(square) ((square + bricks[square / 8]) / dim)

bool is_integer(const string& str)
{
    if (str.empty()) return false;

    for (const char& ch: str)
    {
        if (!isdigit(ch)) return false;
    }

    return true;
}

vector<string> split_string(const string& str, char delimiter)
{
    vector<string> result;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter))
    {
        result.push_back(token);
    }

    return result;
}

vector<string> split_board(const string& board)
{
    vector<string> rows = split_string(board, '/');

    vector<string> output;
    for (auto row = rows.rbegin(); row != rows.rend(); ++row)
    {
        vector<string> cols = split_string(*row, ',');

        for (string col: cols)
        {
            output.push_back(col);
        }
    }

    return output;
}

bool parse_piece(char ch, Piece& piece)
{
    switch (ch)
    {
        case 'P': piece = Pawn;   break;
        case 'N': piece = Knight; break;
        case 'B': piece = Bishop; break;
        case 'R': piece = Rook;   break;
        case 'Q': piece = Queen;  break;
        case 'K': piece = King;   break;

        default: return false;  
    }

    return true;
}

bool parse_player(char ch, Player& player)
{
    switch (ch)
    {
        case 'r': player = Red;    break;
        case 'b': player = Blue;   break;
        case 'y': player = Yellow; break;
        case 'g': player = Green;  break;

        default: return false;
    }

    return true;
}

bool parse_board(const string& board, Position& pos)
{
    vector<string> parts = split_board(board);

    unsigned int count = 0;
    for (const string& part: parts)
    {
        if (is_integer(part))
        {
            count += stoi(part);
        }

        else if (part.size() >= 2)
        {
            Piece piece;
            Player player;

            if (!parse_player(part[0], player)) continue;
            if (!parse_piece(part[1], piece)) continue;
    
            pos.place(count++, piece, player);
        }

        if (count >= board_size) break;
    }

    return count == board_size;
}


string substring(string str, char start, char end)
{
    size_t l = str.find(start);
    size_t r = str.rfind(end);

    if (l != string::npos && r != string::npos)
    {
        return str.substr(l + 1, r - l -1);
    }

    return "";
}

bool parse_digit(char ch, int& digit)
{
    if (ch >= '0' && ch <= '9')
    {
        digit = ch - '0';
    }

    else return false;

    return true;
}

bool parse_integer(string str, int& integer)
{
    int digit;
    integer = 0;
    
    if (str.empty())
    {
        return false;
    }

    for (int i = 0; i < str.size(); i++)
    {
        if (parse_digit(str[i], digit))
        {
            integer = integer * 10 + digit;
        }

        else return false;
    }

    return true;
}

bool parse_location(string loc, Square& sq)
{
    int row, col;

    if (loc.size() < 2)
    {
        return false;
    }

    char c = tolower(loc[0]);

    if (c >= 'a' && c <= 'n')
    {
        col = c - 'a';
    }

    else return false;

    if (parse_integer(loc.substr(1), row))
    {
        row--;
    }

    else return false;

    if (valid_square(row, col))
    {
        sq = Spot(row, col);
    }

    else return false;

    return true;
}

bool parse_enpassant(string enpassant, Position& pos)
{
    vector<string> locations = split_string(substring(enpassant, '(', ')'), ',');

    if (locations.size() != 4)
    {
        return false;
    } 

    for (Player p = Red; p <= Green; ++p)
    //for (int p = 0; p <= 3; ++p)
    {
        vector<string> parts = split_string(substring(locations[p], '\'', '\''), ':');

        if (parts.empty())
        {
            pos.marked[p] = offboard;
            pos.target[p] = offboard;    
        }

        else if (parts.size() == 2)
        {
            bool r1 = parse_location(parts[0], pos.marked[p]);
            bool r2 = parse_location(parts[1], pos.target[p]);

            if (!(r1 && r2)) return false;
        }

        else return false;
    }

    return true;
}

/*
bool parse_fen(const string& fen, Position& pos)
{
    vector<string> parts = split(fen, '-');

    if (parts.size() < 6 || parts.size() > 9) return false;

    string turn = parts[0];

    parse_

    if (parse_turn(parts[0], pos) == false) return false;
    if (parse_rights(parts[0], KingSide, pos) == false) return false;
    if (parse_rights(parts[0], QueenSide, pos) == false) return false;

    return true;
}

bool parse_turn(const string& turn, Position& pos)
{
    if (turn.length() != 1) return false;
    
    switch (turn[0])
    {
        case 'R': pos.turn = Red;    break;
        case 'B': pos.turn = Blue;   break;
        case 'Y': pos.turn = Yellow; break;
        case 'G': pos.turn = Green;  break;
        
        default: return false;
    }

    return true;
}

bool parse_right(const string& right, const Side& side, Position& pos)
{
    vector<string> parts = split(right, ',');

    if (parts.size() != 4) return false;

    for (Player player = Red; player <= Green; ++player)
    {
        switch (parts[player][0])
        {
            case '1': pos.rights[player][side] = true; break;
            case '0': pos.rights[player][side] = false; break;

            default: return false;
        }
    }

    return true;
}

*/
}; // namespace