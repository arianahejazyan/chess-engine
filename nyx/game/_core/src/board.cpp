#include "../include/board.h"
#include "../utils/constants.h"
#include "../utils/utils.h"

using namespace CONSTANTS;

/* ---------------------------------------------------------------------------- */

bool Board::makeMove(Position& pos, const Move& move)
{
    /* move piece */
    if (!(move.flag & Pass)) {
        place(pos, move.to, move.piece, pos.turn);
        remove(pos, move.from);       
    }

    /* update royal location */
    if (pos.royals[pos.turn] == move.from) pos.royals[pos.turn] == move.to;

    /* mark enpassant square */
    if (move.flag & DoublePush) {
        pos.mark[pos.turn]   = move.midway;
        pos.target[pos.turn] = move.to;
    } else {
        pos.mark[pos.turn]   = X;
        pos.target[pos.turn] = X;
    }

    /* remove enssapant pieces */
    if (move.flag & Enpassant) {
        for (const Color& opponent: OPPONENT_LIST[pos.turn]) {
            if (pos.mark[opponent] == move.to) remove(pos, pos.target[opponent]);
        }
    }

    /* move rook after castle */
    if (move.flag & Castle) {
        if (!isPathEmpty(pos, move.passing_squares)) return false;
        place(pos, info.rook_target, Rook, pos.turn);
        remove(pos, info.rook_source);
    }

    /* handle capture */
    if (move.flag & Capture) {}

    /* promote pawn */
    if (move.flag & Promotion) place(pos, move.to, move.promotion, pos.turn);

    /* handle royal safty */
    if (config.rules.capture_the_king) return true;

    /* is castling possible */
    if (move.flag & Castle) return isPathSafe(pos, move.secure_squares);

    /* is royal safe */
    return isSquareSafe(pos, pos.royals[pos.turn]);
}

/* ---------------------------------------------------------------------------- */

void Board::place(Position& pos, const Square& sq, const Piece& piece, const Color& player)
{
    pos.pieces[sq] = piece;
    pos.players[sq] = player;
}

void Board::remove(Position& pos, const Square& sq)
{
    pos.pieces[sq] = Empty;
    pos.players[sq] = None;
}

/* ---------------------------------------------------------------------------- */

bool Board::isOpponentAttacker(const Position& pos, const Move& move)
{
    if ((pos.pieces[move.to] & move.piece) && (isOpponent(pos.turn, pos.players[move.to]))) return true;
}

bool Board::isSquareSafe(const Position& pos, const Square& sq)
{
    for (const Move& move: PSEUDO_MOVES[Key(Leap, sq, Empty, None, S)]) {
        if (isOpponentAttacker(pos, move)) return false;
    }

    for (const Offset& offset: PSEUDO_RAY[Ray(Slide, Empty)]) {
        for (const Move& move: PSEUDO_MOVES[Key(Slide, sq, Empty, None, offset)]) {
            if (pos.pieces[move.to] != Empty) {
                if (isOpponentAttacker(pos, move)) return false;
                break;           
            }
        }
    }
    
    for (const Color& opppnent: OPPONENT_LIST[pos.turn]) {
        for (const Move& move: PSEUDO_MOVES[Key(Advance, sq, Empty, opppnent, S)]) {
            if (isOpponentAttacker(pos, move)) return false;
        }
    }

    return true;
}

bool Board::isPathSafe(const Position& pos, const vector<Square>& path)
{
    for (const Square& sq: path) if (!isSquareSafe(pos, sq)) return false;
    return true;
}

bool Board::isPathEmpty(const Position& pos, const vector<Square>& path)
{
    for (const Square& sq: path) if (pos.pieces[sq] != Empty) return false;
    return true;
}

/* ---------------------------------------------------------------------------- */