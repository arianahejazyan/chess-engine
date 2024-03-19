#include "../include/move_generator.h"
#include "../../utils/constants.h"
#include "../../utils/utils.h"

using namespace CONSTANTS;

/* ---------------------------------------------------------------------------- */

void MoveGenerator::generate_all_moves(const Position& pos, vector<Move>& move_list)
{
    for (const Square& sq: VALID_SQUARES) {
        if (pos.turn == pos.players[sq]) generate_moves(pos, sq, move_list);
    }

    castle(pos, move_list);
    pass(move_list);
}

/* ---------------------------------------------------------------------------- */

void MoveGenerator::generate_moves(const Position& pos, const Square& sq, vector<Move>& move_list)
{
    leap(pos, sq, move_list);
    slide(pos, sq, move_list);
    push(pos, sq, move_list);
    advance(pos, sq, move_list);
}


void MoveGenerator::leap(const Position& pos, const Square& sq, vector<Move>& move_list)
{
    for (const Move& move: PSEUDO_MOVES[Key(Leap, sq, pos.pieces[sq], None, S)]) {
        add_move(pos, move, move_list);
    }
}

void MoveGenerator::slide(const Position& pos, const Square& sq, vector<Move>& move_list)
{
    for (const Offset& offset: PSEUDO_RAY[Ray(Slide, pos.pieces[sq])]) {
        for (const Move& move: PSEUDO_MOVES[Key(Slide, sq, pos.pieces[sq], None, offset)]) {
            add_move(pos, move, move_list);
            if (pos.pieces[move.to] != Empty) break;
        }        
    }
}

void MoveGenerator::push(const Position& pos, const Square& sq, vector<Move>& move_list)
{
    for (const Move& move: PSEUDO_MOVES[Key(Push, sq, pos.pieces[sq], pos.turn, S)]) {
        if (pos.pieces[move.to] == Empty) {
            if (move.flag & Push) add_move(pos, move, move_list);
            else if (move.flag & DoublePush) if (pos.pieces[move.midway] == Empty) add_move(pos, move, move_list);
        }
    }
}

void MoveGenerator::advance(const Position& pos, const Square& sq, vector<Move>& move_list)
{
    for (const Move& move: PSEUDO_MOVES[Key(Advance, sq, pos.pieces[sq], pos.turn, S)]) {
        if (pos.pieces[move.to] != Empty) add_move(pos, move, move_list);
        else if (config.rules.enpassant) {
            for (const Color& opppnent: OPPONENT_LIST[pos.turn]) {
                if (pos.marked[opppnent] == move.to) {
                    move.flag ^= Enpassant;
                    add_move(pos, move, move_list);
                    break;
                }
            }
        }
    }
}

void MoveGenerator::castle(const Position& pos, vector<Move>& move_list)
{
    for (const Move& move: PSEUDO_MOVES[Key(Castle, X, Empty, pos.turn, S)])
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

void MoveGenerator::pass(vector<Move>& move_list)
{
    if (config.rules.allow_passing) move_list.push_back(Move(X,X,Pass));
}

/* ---------------------------------------------------------------------------- */

void MoveGenerator::add_move(const Position& pos, Move move, vector<Move>& move_list)
{
    if (pos.pieces[decodeTo(move)] != Empty) {
        if (isOpponent(pos.turn, pos.players[decodeTo(move)])) {
            move.flag ^= Capture;
            move_list.push_back(move);
        }
    } else {
        move_list.push_back(move);
    }
}

/* ---------------------------------------------------------------------------- */