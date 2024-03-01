#include "board.h"
#include "../utils/constants.h"
#include "../utils/utils.h"

using namespace CONSTANTS;

bool Board::make_move(Position& pos, const Move& move)
{
    place(pos, move.to, move.piece, pos.turn);
    remove(pos, move.from);

    if (move.flag & DOUBLEPUSH)
    {
        pos.mark[pos.turn]   = decodeDoublePushSquare(move.info);
        pos.target[pos.turn] = move.to;
    }
    else 
    {
        pos.mark[pos.turn]   = X;
        pos.target[pos.turn] = X;
    }

    if (move.flag & ENPASSANT)
    {
        for (const Color& opponent: OPPONENT_LIST[pos.turn])
        {
            if (pos.mark[opponent] == move.to)
            {
                destroy(pos, pos.target[opponent]);
            }
        }
    }

    if (move.flag & CAPTURE)
    {
        if (config.rules.fatal_capture)
        {
            destroy(pos, move.to);
        }

        if (config.rules.atomic)
        {
            explosion(pos, move.to);
        }
    }

    if (move.flag & PROMOTION)
    {
        place(pos, move.to, decodePromotePiece(move.info), pos.turn);
    } 

    // Update Royals Locations
    if (pos.royals[pos.turn] == move.from)
    {
        pos.royals[pos.turn] == move.to;
    }

    if (config.rules.capture_the_king)
    {
        return true;
    }

    if (move.flag & CASTLE)
    {

    }

    return !isRoyalcheck(pos);
}

void Board::place(Position& pos, const Square& sq, const Piece& piece, const Color& player)
{
    pos.pieces[sq] = piece;
    pos.players[sq] = player;
}

void Board::remove(Position& pos, const Square& sq)
{
    pos.pieces[sq] = empty;
    pos.players[sq] = none;
}

void Board::destroy(Position& pos, const Square& sq)
{
    if (config.rules.fatal_capture)
    {
        pos.players[sq] = dead;
    }
    else
    {
        remove(pos, sq);
    }
}

void Board::explosion(Position& pos, const Square& sq)
{
    for (const Square& loc: BLAST_SITE[sq])
    {
        if (pos.pieces[loc] != empty)
        {
            if (pos.pieces[loc] & ~PROTECTED_PIECES)
            {
                destroy(pos, loc);
            }
        }
    }

    destroy(pos, sq);
}

bool Board::isSquareCkecked(const Position& pos)
{
    for () {
        if (pos.pieces[sq] == King) return true;
    }

    for () {
        if (pos.pieces[sq] != empty) {
            if (pos.pieces[sq] == Rook || pos.pieces[sq] == Queen) return true;

            break;
        }
    }

    for (pawn) {

    }

    return false;
}