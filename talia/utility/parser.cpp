#include <sstream>
#include "parser.h"
#include <iostream>
using namespace constants;

namespace parser
{

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

bool parse_enpassant(const string& enpassant, Position& pos)
{
    
}

vector<string> expand(string rank)
{
    vector<string> result;


    return result;
}
*/
/*

bool char_to_piece(char ch, Piece& piece)
{
    switch (ch)
    {
        case 'P': piece = Pawn;
        case 'N': piece = Knight;
        case 'B': piece = Bishop;
        case 'R': piece = Rook;
        case 'Q': piece = Queen;
        case 'K': piece = King;

        default: return false;  
    }

    return true;
}

bool char_to_player(char ch, Player& player)
{
    switch (ch)
    {
        case 'r': player = Red;
        case 'b': player = Blue;
        case 'y': player = Yellow;
        case 'g': player = Green;

        default: return false;
    }

    return true;
}



bool parse_board(const string& board, Position& pos)
{
    // split / then reverse

    if (rows.size() != 14) return false;

    unsigned int rank = 0;
    for (string row: rows)
    {
        // split ,

        unsigned int file = 0;
        for (string col: cols)
        {
            // brick

            // 

            
        }

        if (file != 14) return false;
    }

    if (rank != 14) return false;

    return true;
}
*/
/*
bool parse_board(const string& board, Position& pos)
{
    vector<string> parts = split(replace(board, '/'), ',');

    unsigned int count = 0;
    for (const string& str: board)
    {
        if (str.size() == 0) return false;

        unsigned int empty;
        if (string_to_integer(str, empty))
        {
            count += empty;
        }

        Piece piece;
        Player player;

        if (str.size() == 2 && char_to_piece(str[0], piece) && char_to_player(str[1], player))
        {
            count++;
        }
    }

    return count == board_size;
}

bool parse_board3(const string& board, Position& pos)
{
    vector<string> squares = split(convert(board), ',');

    if (squares.size() != board_size) return false;

    for (int sq = 0; sq < board_size; ++sq)
    {
        pos.pieces[sq] = string_to_piece(squares[sq]);
        pos.players[sq] = string_to_player(squares[sq]);
    }

    return true;
}

bool parse_board2(const string& board, Position& pos)
{
    vector<string> rows = split(board, '/');

    std::reverse(rows.begin(), rows.end());

    int rank = 0;
    for (const string& line: rows)
    {
        vector<string> cols = split(line, ',');

        int file = 0;
        int bricks = 0;
        for (const string& element: cols)
        {
            if (element.size() == 0) return false;

            // check if square is a brick
            if (std::tolower(element[0]) == 'x') 
            {
                file++;
                bricks++;
            }

            // check if square is empty
            else if (numerical(element))
            {
                file += (std::stoi(element) - 1);
            }

            // check if square is valid piece
            Piece piece;
            Player player;
            if (conver(sq))
            {

            }



            else if (element.size() == 2)
            {
                Square loc = static_cast<Square>(rank * 14 + file - bricks);

                // extract player and update position
                switch (lower(element[0]))
                {
                    case 'r': pos.players[loc] = Red;    break;
                    case 'b': pos.players[loc] = Blue;   break;
                    case 'y': pos.players[loc] = Yellow; break;
                    case 'g': pos.players[loc] = Green;  break;
                
                    default: return false;
                }

                // extract piece and update position
                switch (upper(element[1]))
                {
                    case 'P': pos.pieces[loc] = Pawn;   break;
                    case 'N': pos.pieces[loc] = Knight; break;
                    case 'B': pos.pieces[loc] = Bishop; break;
                    case 'R': pos.pieces[loc] = Rook;   break;
                    case 'Q': pos.pieces[loc] = Queen;  break;
                    case 'K': pos.pieces[loc] = King;   break;

                    default: return false;
                }
            }

            else return false;

            ++file;
        }

         if (file != 13) return false;

         ++rank;
    }

    if (rank != 13) return false;

    return true;
}
*/
}; // namespace