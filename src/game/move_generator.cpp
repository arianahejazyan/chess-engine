#include "move_generator.h"

/* ---------------------------------------------------------------------------- */

void MoveGenerator::generate_all_moves(const Position& pos, vector<int>& move_list)
{
    for (const Square& sq: VALID_SQUARES)
    {
        if (pos.turn == pos.players[sq])
        {
            generate_moves(pos, sq, move_list);
        }
    }

    castle(pos, move_list);

    pass(move_list);
}

void MoveGenerator::generate_moves(const Position& pos, const Square& sq, vector<int>& move_list)
{
    int type = PIECE_TYPE[pos.pieces[sq]];

    if (type & LEAP)   leap(pos, sq, move_list);
    if (type & SLIDE)  slide(pos, sq, move_list);
    if (type & PUSH)   push(pos, sq, move_list);
    if (type & ATTACK) attack(pos, sq, move_list);
    if (type & CRAWL)  crawl(pos, sq, move_list);
    if (type & HOP)    hop(pos, sq, move_list);
}

/* ---------------------------------------------------------------------------- */

void MoveGenerator::leap(const Position& pos, const Square& sq, vector<int>& move_list)
{
    for (const int& move: LEAP_MOVES[sq | (pos.pieces[sq] << SQUARE_SIZE)])
    {
        Flag flag = decodeFlag(move);

        if (flag & LEAP)
        {
            add_move(pos, move, move_list);
        }
        
        else if (flag & CRAWL)
        {
            if ()
            {
                add_move(pos, move, move_list);
            }
        }
    }
}

void MoveGenerator::slide(const Position& pos, const Square& sq, vector<int>& move_list)
{
    for (constexpr Offset offset: {U, D, R, L})
    {
        for (const int& move: SLIDE_MOVES[sq | (offset << SQUARE_SIZE)])
        {
            add_move(pos, move, move_list);

            if (pos.pieces[decodeTo(move)] != empty) break;
        }        
    }
}

void MoveGenerator::push(const Position& pos, const Square& sq, vector<int>& move_list)
{
    for (const int& move: PUSH_MOVES[sq | (pos.pieces[sq] << SQUARE_SIZE) | (pos.turn << PIECE_SIZE)])
    {
        Flag flag = decodeFlag(move);

        if (flag & PUSH)
        {
            if (pos.pieces[decodeTo(move)] == empty)
            {
                add_move(pos, move, move_list);
            }
        }

        else if (flag & DOUBLEPUSH)
        {
            if (pos.pieces[decodeTo(move)] == empty &&  pos.pieces[(decodeTo(move) + sq) / 2] == empty)
            {
                add_move(pos, move, move_list);
            }
        }

        else if (flag & SIDEPUSH)
        {
            if (pos.pieces[decodeTo(move)] == empty)
            {
                add_move(pos, move, move_list);
            }
        }
    }
}

void MoveGenerator::attack(const Position& pos, const Square& sq, vector<int>& move_list)
{
    for (const int& move: ATTACK_MOVES[sq | (pos.pieces[sq] << SQUARE_SIZE) | (pos.turn << PIECE_SIZE)])
    {
        if (pos.pieces[decodeTo(move)] != empty)
        {
            add_move(pos, move, move_list);
        }

        else if (isMarkedSquare())
        {
            add_move(pos, move ^ decodeFlag(ENPASSANT), move_list);
        }
    }
}

void MoveGenerator::castle(const Position& pos, vector<int>& move_list)
{
    for (const int& move: CASTLE_MOVES[pos.turn])
    {
        if (decodeCastlingRight(pos.rights, decodeCastlingSide(move, pos.turn))) {
            bool valid = true;
            int idx = 0;

            while (idx++ < decodeCastlingSteps(move)) {
                if (pos.pieces[decodePassingSqaures(move, idx)] == empty) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                add_move(pos, move, move_list);
            }
        }
    }
}

void MoveGenerator::pass(vector<int>& move_list)
{
    if (config.rules.allow_passing)
    {
        move_list.push_back(encode_move(X, X, PASS));
    }
}

/* ---------------------------------------------------------------------------- */

void MoveGenerator::add_move(const Position& pos, int move, vector<int>& move_list)
{
    if (pos.pieces[decodeTo(move)] != empty)
    {
        if (config.rules.any_capture || isOpponent(pos.turn, pos.players[decodeTo(move)]))
        {
            move_list.push_back(move ^ encodeFlag(CAPTURE));
        }
    }

    else
    {
        move_list.push_back(move);
    }
}

/* ---------------------------------------------------------------------------- */